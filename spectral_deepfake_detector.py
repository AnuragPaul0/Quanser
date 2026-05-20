"""
Spectral Deepfake Detector
Implementation of: "Watch your Up-Convolution: CNN Based Generative Deep Neural Networks
are Failing to Reproduce Spectral Distributions" (arXiv:2003.01826)

Usage:
    python spectral_deepfake_detector.py --dataset /path/to/FakeAVCeleb_faces
    python spectral_deepfake_detector.py --real /path/to/real --fake /path/to/fake

Expected folder structure (either format works):
    Option A - FakeAVCeleb style:
        dataset/
            RealVideo-RealAudio/   (or any folder with 'real' in name)
            FakeVideo-RealAudio/   (or any folder with 'fake' in name)

    Option B - explicit:
        real/   <- real face images
        fake/   <- fake/deepfake face images

Images can be nested in subfolders (e.g. per-video folders).
Supported formats: .jpg, .jpeg, .png, .bmp, .tiff
"""

import os
import sys
import argparse
import warnings
import json
warnings.filterwarnings("ignore")

import numpy as np
from pathlib import Path
from PIL import Image
import cv2

from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import StratifiedKFold, cross_val_predict
from sklearn.metrics import (accuracy_score, roc_auc_score, classification_report,
                              confusion_matrix, roc_curve)
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from matplotlib.colors import LinearSegmentedColormap
from scipy.ndimage import uniform_filter1d


# ─────────────────────────────────────────────
# Core spectral feature extraction (paper §3)
# ─────────────────────────────────────────────

def to_grayscale(img_array):
    """Convert image array to grayscale float."""
    if img_array.ndim == 3:
        return cv2.cvtColor(img_array, cv2.COLOR_RGB2GRAY).astype(np.float32)
    return img_array.astype(np.float32)


def azimuthal_average(power_spectrum):
    """
    Compute the azimuthal (radial) average of a 2D power spectrum.
    Returns 1D array of mean power at each frequency radius.
    """
    h, w = power_spectrum.shape
    cy, cx = h // 2, w // 2
    y, x = np.ogrid[:h, :w]
    r = np.sqrt((x - cx)**2 + (y - cy)**2).astype(int)
    max_r = min(cx, cy)
    avg = np.zeros(max_r)
    for i in range(max_r):
        mask = r == i
        if mask.any():
            avg[i] = power_spectrum[mask].mean()
    return avg


def extract_spectral_features(image_path, img_size=128, n_bins=64):
    """
    Extract spectral feature vector from an image.
    
    Steps (from paper):
    1. Resize & grayscale
    2. 2D FFT → shift DC to center
    3. Log power spectrum
    4. Azimuthal average → 1D frequency profile
    5. Normalize and bin
    """
    try:
        img = Image.open(image_path).convert("RGB")
        img = img.resize((img_size, img_size), Image.LANCZOS)
        img_array = np.array(img)
        gray = to_grayscale(img_array)

        # 2D FFT
        fft = np.fft.fft2(gray)
        fft_shift = np.fft.fftshift(fft)
        power = np.abs(fft_shift) ** 2
        log_power = np.log1p(power)

        # Azimuthal average
        radial = azimuthal_average(log_power)

        # Bin into fixed-size feature vector
        # Interpolate to n_bins for consistent feature length
        bins = np.linspace(0, len(radial) - 1, n_bins)
        feature = np.interp(bins, np.arange(len(radial)), radial)

        # L2 normalize
        norm = np.linalg.norm(feature)
        if norm > 0:
            feature = feature / norm
        return feature
    except Exception as e:
        return None


def extract_2d_power_spectrum(image_path, img_size=128):
    """Return 2D log power spectrum (for visualization)."""
    try:
        img = Image.open(image_path).convert("RGB")
        img = img.resize((img_size, img_size), Image.LANCZOS)
        gray = to_grayscale(np.array(img))
        fft = np.fft.fft2(gray)
        fft_shift = np.fft.fftshift(fft)
        power = np.abs(fft_shift) ** 2
        return np.log1p(power)
    except:
        return None


# ─────────────────────────────────────────────
# Data loading
# ─────────────────────────────────────────────

IMG_EXTS = {".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".webp"}

def find_images(folder, max_per_class=2000):
    """Recursively find image paths in a folder."""
    paths = []
    for root, dirs, files in os.walk(folder):
        for f in files:
            if Path(f).suffix.lower() in IMG_EXTS:
                paths.append(os.path.join(root, f))
    # Shuffle for diversity if capping
    np.random.shuffle(paths)
    return paths[:max_per_class]


def auto_detect_splits(dataset_root):
    """
    Auto-detect real/fake subfolders from a dataset root.
    Handles FakeAVCeleb structure and generic real/fake naming.
    """
    root = Path(dataset_root)
    subdirs = [d for d in root.iterdir() if d.is_dir()]
    
    real_dirs, fake_dirs = [], []
    for d in subdirs:
        name = d.name.lower()
        if "real" in name and "fake" not in name:
            real_dirs.append(str(d))
        elif "fake" in name or "synth" in name or "generated" in name:
            fake_dirs.append(str(d))
    
    return real_dirs, fake_dirs


def load_dataset(real_dirs, fake_dirs, max_per_class=2000, n_bins=64, verbose=True):
    """Load images and extract spectral features."""
    real_paths, fake_paths = [], []
    for d in real_dirs:
        real_paths += find_images(d, max_per_class)
    for d in fake_dirs:
        fake_paths += find_images(d, max_per_class)

    real_paths = real_paths[:max_per_class]
    fake_paths = fake_paths[:max_per_class]

    if verbose:
        print(f"  Found {len(real_paths)} real images, {len(fake_paths)} fake images")

    def extract_batch(paths, label_name):
        features, paths_ok = [], []
        total = len(paths)
        for i, p in enumerate(paths):
            if verbose and (i % 200 == 0):
                print(f"    Processing {label_name}: {i}/{total}", end="\r")
            feat = extract_spectral_features(p, n_bins=n_bins)
            if feat is not None:
                features.append(feat)
                paths_ok.append(p)
        if verbose:
            print(f"    Processing {label_name}: {len(features)}/{total} OK   ")
        return features, paths_ok

    real_feats, real_ok = extract_batch(real_paths, "real")
    fake_feats, fake_ok = extract_batch(fake_paths, "fake")

    X = np.array(real_feats + fake_feats)
    y = np.array([0] * len(real_feats) + [1] * len(fake_feats))
    paths_all = real_ok + fake_ok

    return X, y, paths_all, real_ok, fake_ok


# ─────────────────────────────────────────────
# Visualization
# ─────────────────────────────────────────────

def plot_results(X, y, paths_real, paths_fake, y_pred, y_prob, report_str, cm,
                 n_bins=64, out_path="spectral_results.png"):
    """
    Generate a comprehensive results figure with:
    1. Mean spectral profiles (real vs fake)
    2. Mean 2D power spectrum (real vs fake)
    3. Sample face grids
    4. ROC curve
    5. Confusion matrix
    6. Classification metrics
    """
    # Compute mean spectral profiles
    real_feats = X[y == 0]
    fake_feats = X[y == 1]
    mean_real = real_feats.mean(axis=0)
    mean_fake = fake_feats.mean(axis=0)
    std_real = real_feats.std(axis=0)
    std_fake = fake_feats.std(axis=0)
    freqs = np.linspace(0, 1, n_bins)

    # Compute mean 2D power spectra (sample up to 200)
    def mean_2d_spectrum(paths, n=200):
        specs = []
        for p in paths[:n]:
            s = extract_2d_power_spectrum(p)
            if s is not None:
                specs.append(s)
        return np.mean(specs, axis=0) if specs else None

    print("  Computing mean 2D spectra for visualization...")
    spec2d_real = mean_2d_spectrum(paths_real)
    spec2d_fake = mean_2d_spectrum(paths_fake)

    # ROC
    fpr, tpr, _ = roc_curve(y, y_prob)
    auc = roc_auc_score(y, y_prob)

    # ── Layout ──
    fig = plt.figure(figsize=(20, 16), facecolor="#0d0d0d")
    fig.patch.set_facecolor("#0d0d0d")

    gs = gridspec.GridSpec(3, 4, figure=fig, hspace=0.45, wspace=0.35,
                           top=0.93, bottom=0.05, left=0.06, right=0.97)

    REAL_COLOR = "#00e5c0"
    FAKE_COLOR = "#ff4b6e"
    GRID_COLOR = "#2a2a2a"
    TEXT_COLOR = "#e8e8e8"

    ax_style = dict(facecolor="#141414", labelcolor=TEXT_COLOR, labelsize=10)

    def style_ax(ax, title=""):
        ax.set_facecolor("#141414")
        ax.tick_params(colors=TEXT_COLOR, labelsize=8)
        ax.xaxis.label.set_color(TEXT_COLOR)
        ax.yaxis.label.set_color(TEXT_COLOR)
        for spine in ax.spines.values():
            spine.set_color("#333333")
        if title:
            ax.set_title(title, color=TEXT_COLOR, fontsize=10, fontweight="bold", pad=8)
        ax.grid(True, color=GRID_COLOR, linewidth=0.5, alpha=0.7)

    # ── Title ──
    fig.text(0.5, 0.97, "Spectral Deepfake Detection  ·  arXiv:2003.01826",
             ha="center", va="top", color=TEXT_COLOR,
             fontsize=15, fontweight="bold", family="monospace")

    # ── 1. Spectral profiles ──
    ax1 = fig.add_subplot(gs[0, :2])
    smooth_real = uniform_filter1d(mean_real, size=3)
    smooth_fake = uniform_filter1d(mean_fake, size=3)
    ax1.fill_between(freqs, smooth_real - std_real, smooth_real + std_real,
                     alpha=0.2, color=REAL_COLOR)
    ax1.fill_between(freqs, smooth_fake - std_fake, smooth_fake + std_fake,
                     alpha=0.2, color=FAKE_COLOR)
    ax1.plot(freqs, smooth_real, color=REAL_COLOR, lw=2, label="Real")
    ax1.plot(freqs, smooth_fake, color=FAKE_COLOR, lw=2, label="Fake")
    ax1.set_xlabel("Normalized Frequency")
    ax1.set_ylabel("Normalized Log Power")
    style_ax(ax1, "Mean Azimuthal Spectral Profile")
    ax1.legend(facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT_COLOR,
               fontsize=9, loc="upper right")

    # ── 2. Spectral difference ──
    ax2 = fig.add_subplot(gs[0, 2:])
    diff = smooth_fake - smooth_real
    ax2.axhline(0, color="#555", lw=1, ls="--")
    ax2.fill_between(freqs, diff, 0,
                     where=(diff > 0), alpha=0.6, color=FAKE_COLOR, label="Fake > Real")
    ax2.fill_between(freqs, diff, 0,
                     where=(diff < 0), alpha=0.6, color=REAL_COLOR, label="Real > Fake")
    ax2.plot(freqs, diff, color="#ffffff", lw=1.2, alpha=0.7)
    ax2.set_xlabel("Normalized Frequency")
    ax2.set_ylabel("Δ Log Power (Fake − Real)")
    style_ax(ax2, "Spectral Difference: Fake − Real")
    ax2.legend(facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT_COLOR, fontsize=9)

    # ── 3 & 4. 2D power spectra ──
    cmap = LinearSegmentedColormap.from_list("heatmap",
           ["#0d0d0d", "#1a0a2e", "#6a0572", "#e91e63", "#ff9800", "#ffeb3b"])

    for col, (spec2d, label, color) in enumerate(
            [(spec2d_real, "Real", REAL_COLOR), (spec2d_fake, "Fake", FAKE_COLOR)]):
        ax = fig.add_subplot(gs[1, col])
        if spec2d is not None:
            im = ax.imshow(spec2d, cmap=cmap, origin="lower", aspect="equal")
            plt.colorbar(im, ax=ax, fraction=0.046, pad=0.04).ax.tick_params(
                colors=TEXT_COLOR, labelsize=7)
        ax.set_xticks([])
        ax.set_yticks([])
        for spine in ax.spines.values():
            spine.set_color(color)
            spine.set_linewidth(2)
        ax.set_title(f"Mean 2D Power Spectrum\n({label})",
                     color=color, fontsize=10, fontweight="bold", pad=8)

    # ── 5. ROC curve ──
    ax5 = fig.add_subplot(gs[1, 2])
    ax5.plot(fpr, tpr, color="#7c4dff", lw=2.5, label=f"AUC = {auc:.3f}")
    ax5.plot([0, 1], [0, 1], "--", color="#555", lw=1)
    ax5.fill_between(fpr, tpr, alpha=0.15, color="#7c4dff")
    ax5.set_xlabel("False Positive Rate")
    ax5.set_ylabel("True Positive Rate")
    style_ax(ax5, "ROC Curve")
    ax5.legend(facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT_COLOR, fontsize=9)
    ax5.set_xlim([0, 1])
    ax5.set_ylim([0, 1.02])

    # ── 6. Confusion matrix ──
    ax6 = fig.add_subplot(gs[1, 3])
    cm_norm = cm.astype(float) / cm.sum(axis=1, keepdims=True)
    im = ax6.imshow(cm_norm, cmap="magma", vmin=0, vmax=1)
    ax6.set_xticks([0, 1])
    ax6.set_yticks([0, 1])
    ax6.set_xticklabels(["Real", "Fake"], color=TEXT_COLOR, fontsize=9)
    ax6.set_yticklabels(["Real", "Fake"], color=TEXT_COLOR, fontsize=9, rotation=90, va="center")
    for (i, j), val in np.ndenumerate(cm):
        ax6.text(j, i, f"{val}\n({cm_norm[i,j]:.1%})",
                 ha="center", va="center", color="white", fontsize=9, fontweight="bold")
    ax6.set_xlabel("Predicted", color=TEXT_COLOR, fontsize=9)
    ax6.set_ylabel("Actual", color=TEXT_COLOR, fontsize=9)
    style_ax(ax6, "Confusion Matrix")
    plt.colorbar(im, ax=ax6, fraction=0.046, pad=0.04).ax.tick_params(
        colors=TEXT_COLOR, labelsize=7)

    # ── 7. Sample images: real ──
    ax7 = fig.add_subplot(gs[2, :2])
    ax7.set_facecolor("#0d0d0d")
    ax7.axis("off")
    ax7.set_title("Sample Real Faces", color=REAL_COLOR, fontsize=10,
                  fontweight="bold", pad=8)
    n_samples = min(8, len(paths_real))
    sample_paths = paths_real[:n_samples]
    for i, p in enumerate(sample_paths):
        try:
            img = Image.open(p).convert("RGB").resize((64, 64))
            inset = fig.add_axes([0.06 + i * 0.115, 0.03, 0.1, 0.1])
            inset.imshow(np.array(img))
            inset.axis("off")
            for spine in inset.spines.values():
                spine.set_color(REAL_COLOR)
                spine.set_linewidth(2)
        except:
            pass

    # ── 8. Sample images: fake ──
    ax8 = fig.add_subplot(gs[2, 2:])
    ax8.set_facecolor("#0d0d0d")
    ax8.axis("off")
    ax8.set_title("Sample Fake Faces", color=FAKE_COLOR, fontsize=10,
                  fontweight="bold", pad=8)
    for i, p in enumerate(paths_fake[:n_samples]):
        try:
            img = Image.open(p).convert("RGB").resize((64, 64))
            inset = fig.add_axes([0.535 + i * 0.115, 0.03, 0.1, 0.1])
            inset.imshow(np.array(img))
            inset.axis("off")
            for spine in inset.spines.values():
                spine.set_color(FAKE_COLOR)
                spine.set_linewidth(2)
        except:
            pass

    plt.savefig(out_path, dpi=150, bbox_inches="tight", facecolor="#0d0d0d")
    plt.close()
    print(f"  Saved visualization → {out_path}")


# ─────────────────────────────────────────────
# Main pipeline
# ─────────────────────────────────────────────

def run(real_dirs, fake_dirs, max_per_class=2000, n_bins=64,
        out_dir="spectral_output"):

    os.makedirs(out_dir, exist_ok=True)

    print("\n📂 Loading dataset and extracting spectral features...")
    X, y, paths_all, paths_real, paths_fake = load_dataset(
        real_dirs, fake_dirs, max_per_class=max_per_class, n_bins=n_bins)

    if len(X) < 10:
        print("❌ Not enough valid images found. Check folder paths.")
        sys.exit(1)

    print(f"\n📊 Dataset: {(y==0).sum()} real | {(y==1).sum()} fake  →  {len(X)} total\n")

    # ── Classifier (paper uses LDA/SVM; we use both) ──
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)

    cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)

    print("🔬 Training Logistic Regression classifier (5-fold CV)...")
    clf_lr = LogisticRegression(C=1.0, max_iter=1000, random_state=42)
    y_pred_lr = cross_val_predict(clf_lr, X_scaled, y, cv=cv)
    y_prob_lr = cross_val_predict(clf_lr, X_scaled, y, cv=cv, method="predict_proba")[:, 1]

    print("🔬 Training SVM classifier (5-fold CV)...")
    clf_svm = SVC(kernel="rbf", C=10, probability=True, random_state=42)
    y_pred_svm = cross_val_predict(clf_svm, X_scaled, y, cv=cv)
    y_prob_svm = cross_val_predict(clf_svm, X_scaled, y, cv=cv, method="predict_proba")[:, 1]

    # Pick best
    acc_lr = accuracy_score(y, y_pred_lr)
    acc_svm = accuracy_score(y, y_pred_svm)
    best_name = "SVM" if acc_svm >= acc_lr else "Logistic Regression"
    y_pred = y_pred_svm if acc_svm >= acc_lr else y_pred_lr
    y_prob  = y_prob_svm if acc_svm >= acc_lr else y_prob_lr

    auc = roc_auc_score(y, y_prob)
    cm  = confusion_matrix(y, y_pred)
    report = classification_report(y, y_pred, target_names=["Real", "Fake"])

    print(f"\n{'='*52}")
    print(f" Results — Best Classifier: {best_name}")
    print(f"{'='*52}")
    print(f"  Accuracy    : {accuracy_score(y, y_pred):.4f}  ({accuracy_score(y, y_pred)*100:.2f}%)")
    print(f"  ROC-AUC     : {auc:.4f}")
    print(f"\n  Logistic Regression Acc : {acc_lr:.4f}")
    print(f"  SVM Acc                 : {acc_svm:.4f}")
    print(f"\n{report}")
    print(f"{'='*52}\n")

    # ── Save metrics JSON ──
    metrics = {
        "n_real": int((y==0).sum()),
        "n_fake": int((y==1).sum()),
        "best_classifier": best_name,
        "accuracy": float(accuracy_score(y, y_pred)),
        "roc_auc": float(auc),
        "logistic_regression_accuracy": float(acc_lr),
        "svm_accuracy": float(acc_svm),
        "confusion_matrix": cm.tolist(),
    }
    metrics_path = os.path.join(out_dir, "metrics.json")
    with open(metrics_path, "w") as f:
        json.dump(metrics, f, indent=2)
    print(f"📄 Metrics saved → {metrics_path}")

    # ── Visualization ──
    print("\n🎨 Generating visualizations...")
    plot_results(X, y, paths_real, paths_fake, y_pred, y_prob, report, cm,
                 n_bins=n_bins, out_path=os.path.join(out_dir, "spectral_results.png"))

    print(f"\n✅ Done! All outputs in: {out_dir}/")
    return metrics


# ─────────────────────────────────────────────
# CLI
# ─────────────────────────────────────────────

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Spectral Deepfake Detector — arXiv:2003.01826")
    parser.add_argument("--dataset", type=str, default=None,
        help="Root of dataset folder; real/fake subfolders auto-detected")
    parser.add_argument("--real", type=str, default=None,
        help="Explicit path to real images folder")
    parser.add_argument("--fake", type=str, default=None,
        help="Explicit path to fake images folder")
    parser.add_argument("--max", type=int, default=2000,
        help="Max images per class (default: 2000)")
    parser.add_argument("--bins", type=int, default=64,
        help="Spectral feature bins (default: 64)")
    parser.add_argument("--out", type=str, default="spectral_output",
        help="Output directory (default: spectral_output)")
    args = parser.parse_args()

    np.random.seed(42)

    if args.real and args.fake:
        run([args.real], [args.fake], args.max, args.bins, args.out)
    elif args.dataset:
        real_dirs, fake_dirs = auto_detect_splits(args.dataset)
        if not real_dirs or not fake_dirs:
            print(f"❌ Could not auto-detect real/fake folders in: {args.dataset}")
            print("   Try: --real /path/to/real --fake /path/to/fake")
            sys.exit(1)
        print(f"📁 Auto-detected:")
        print(f"   Real : {real_dirs}")
        print(f"   Fake : {fake_dirs}")
        run(real_dirs, fake_dirs, args.max, args.bins, args.out)
    else:
        parser.print_help()
        print("\nExample:\n  python spectral_deepfake_detector.py --dataset ./FakeAVCeleb_faces")
        print("  python spectral_deepfake_detector.py --real ./real --fake ./fake")
