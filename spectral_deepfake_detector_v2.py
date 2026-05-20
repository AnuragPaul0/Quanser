"""
Spectral Deepfake Detector — Cross-Ethnic Generalization Experiment
Based on: arXiv:2003.01826 — "Watch your Up-Convolution"

TRAINING  (3 ethnicities, balanced sampling):
  African, East Asian, South Asian
  Real  : RealVideo-RealAudio  → ALL 32 frames per video
  Fake  : FakeVideo-FakeAudio + FakeVideo-RealAudio → 1 frame per video

TESTING   (held-out ethnicities, zero-shot):
  Caucasian American  → report separately
  Caucasian European  → report separately

EXPECTED FOLDER STRUCTURE (FakeAVCeleb_faces):
  FakeAVCeleb_faces/
    African/
      RealVideo-RealAudio/   id00001/ frame_0001.jpg ...
      FakeVideo-FakeAudio/   id00001/ frame_0001.jpg ...
      FakeVideo-RealAudio/   id00001/ frame_0001.jpg ...
    EastAsian/   (or East_Asian / East Asian)
      ...
    SouthAsian/  (or South_Asian / South Asian)
      ...
    CaucasianAmerican/   (or Caucasian_American / Caucasian-American)
      ...
    CaucasianEuropean/
      ...

Usage:
    python spectral_deepfake_detector_v2.py --dataset /path/to/FakeAVCeleb_faces
    python spectral_deepfake_detector_v2.py --dataset /path/to/FakeAVCeleb_faces --max_real 9489 --max_fake 11230
"""

import os, sys, re, json, argparse, warnings
warnings.filterwarnings("ignore")

import numpy as np
from pathlib import Path
from PIL import Image
import cv2
from collections import defaultdict

from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.metrics import (accuracy_score, roc_auc_score,
                              classification_report, confusion_matrix, roc_curve)

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from matplotlib.colors import LinearSegmentedColormap
from scipy.ndimage import uniform_filter1d

# ─────────────────────────────────────────────
#  Constants
# ─────────────────────────────────────────────

IMG_EXTS = {".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".webp"}
IMG_SIZE  = 128
N_BINS    = 64

# Fuzzy name → canonical key
ETHNICITY_MAP = {
    # Training
    "african"        : "African",
    "black"          : "African",
    # East Asian
    "eastasian"      : "EastAsian",
    "east_asian"     : "EastAsian",
    "east asian"     : "EastAsian",
    "asian_east"     : "EastAsian",
    "asian-east"     : "EastAsian",
    # South Asian
    "southasian"     : "SouthAsian",
    "south_asian"    : "SouthAsian",
    "south asian"    : "SouthAsian",
    "asian_south"    : "SouthAsian",
    "asian-south"    : "SouthAsian",
    # Test
    "caucasianamerican"  : "CaucasianAmerican",
    "caucasian_american" : "CaucasianAmerican",
    "caucasian-american" : "CaucasianAmerican",
    "caucasian american" : "CaucasianAmerican",
    "caucasianeuropean"  : "CaucasianEuropean",
    "caucasian_european" : "CaucasianEuropean",
    "caucasian-european" : "CaucasianEuropean",
    "caucasian european" : "CaucasianEuropean",
}

TRAIN_ETHNICITIES = {"African", "EastAsian", "SouthAsian"}
TEST_ETHNICITIES  = {"CaucasianAmerican", "CaucasianEuropean"}

REAL_FOLDER_KEY   = "realvideorealaudio"
FAKE_FOLDER_KEYS  = {"fakevideofakeaudio", "fakevideorealaudio"}

# ─────────────────────────────────────────────
#  Spectral feature extraction
# ─────────────────────────────────────────────

def azimuthal_average(ps):
    h, w = ps.shape
    cy, cx = h // 2, w // 2
    y, x = np.ogrid[:h, :w]
    r = np.sqrt((x - cx)**2 + (y - cy)**2).astype(int)
    max_r = min(cx, cy)
    avg = np.zeros(max_r)
    for i in range(max_r):
        m = r == i
        if m.any():
            avg[i] = ps[m].mean()
    return avg

def extract_feature(image_path):
    try:
        img = Image.open(image_path).convert("RGB")
        img = img.resize((IMG_SIZE, IMG_SIZE), Image.LANCZOS)
        gray = cv2.cvtColor(np.array(img), cv2.COLOR_RGB2GRAY).astype(np.float32)
        fft  = np.fft.fftshift(np.fft.fft2(gray))
        log_ps = np.log1p(np.abs(fft) ** 2)
        radial = azimuthal_average(log_ps)
        bins   = np.linspace(0, len(radial) - 1, N_BINS)
        feat   = np.interp(bins, np.arange(len(radial)), radial)
        n = np.linalg.norm(feat)
        return feat / n if n > 0 else feat
    except:
        return None

# ─────────────────────────────────────────────
#  Dataset discovery
# ─────────────────────────────────────────────

def normalise(name):
    return re.sub(r"[\s_\-]", "", name).lower()

def find_ethnicity_dirs(root):
    """Map canonical ethnicity keys → folder paths."""
    result = {}
    for d in Path(root).iterdir():
        if not d.is_dir():
            continue
        key = ETHNICITY_MAP.get(normalise(d.name))
        if key:
            result[key] = str(d)
    return result

def find_category_dirs(eth_dir):
    """Within an ethnicity folder, find real/fake category subdirs."""
    cats = {"real": None, "fake_ffa": None, "fake_fra": None}
    for d in Path(eth_dir).iterdir():
        if not d.is_dir():
            continue
        k = normalise(d.name)
        if k == REAL_FOLDER_KEY:
            cats["real"] = str(d)
        elif k == "fakevideofakeaudio":
            cats["fake_ffa"] = str(d)
        elif k == "fakevideorealaudio":
            cats["fake_fra"] = str(d)
    return cats

def get_video_groups(folder):
    """Group images by their parent directory (= one video per subfolder)."""
    groups = defaultdict(list)
    for root, dirs, files in os.walk(folder):
        for f in files:
            if Path(f).suffix.lower() in IMG_EXTS:
                groups[root].append(os.path.join(root, f))
    # Sort frames within each video for reproducibility
    for k in groups:
        groups[k].sort()
    return groups

def sample_real_frames(video_groups, n_frames=32):
    """Take up to n_frames per video, all frames if fewer exist."""
    paths = []
    for frames in video_groups.values():
        paths.extend(frames[:n_frames])
    return paths

def sample_fake_frames(video_groups, n_frames=1):
    """Take exactly 1 frame per video (first frame)."""
    paths = []
    for frames in video_groups.values():
        if frames:
            paths.append(frames[0])
    return paths

# ─────────────────────────────────────────────
#  Feature extraction with progress
# ─────────────────────────────────────────────

def extract_batch(paths, tag, max_n=None):
    if max_n:
        np.random.shuffle(paths)
        paths = paths[:max_n]
    feats, ok = [], []
    total = len(paths)
    for i, p in enumerate(paths):
        if i % 500 == 0:
            print(f"    [{tag}] {i}/{total}", end="\r", flush=True)
        f = extract_feature(p)
        if f is not None:
            feats.append(f)
            ok.append(p)
    print(f"    [{tag}] {len(feats)}/{total} extracted   ")
    return np.array(feats), ok

# ─────────────────────────────────────────────
#  Load split (train or test ethnicities)
# ─────────────────────────────────────────────

def load_split(eth_dirs, ethnicity_set, split_name,
               real_all_frames=True, max_real=None, max_fake=None):
    """
    Returns X, y, paths, per_ethnicity_stats
    real_all_frames=True  → 32 frames/video (training real)
    real_all_frames=False → 1 frame/video  (if needed for test)
    """
    all_real, all_fake = [], []
    stats = {}

    for eth in sorted(ethnicity_set):
        if eth not in eth_dirs:
            print(f"  ⚠  {eth}: folder not found, skipping")
            continue
        cats = find_category_dirs(eth_dirs[eth])

        # REAL
        real_paths = []
        if cats["real"]:
            vg = get_video_groups(cats["real"])
            n  = 32 if real_all_frames else 1
            real_paths = sample_real_frames(vg, n_frames=n)
        else:
            print(f"  ⚠  {eth}: RealVideo-RealAudio not found")

        # FAKE (FFA + FRA, 1 frame each)
        fake_paths = []
        for key in ("fake_ffa", "fake_fra"):
            if cats[key]:
                vg = get_video_groups(cats[key])
                fake_paths += sample_fake_frames(vg, n_frames=1)
            else:
                print(f"  ⚠  {eth}: {key} not found")

        np.random.shuffle(real_paths)
        np.random.shuffle(fake_paths)

        stats[eth] = {"real_raw": len(real_paths), "fake_raw": len(fake_paths)}
        print(f"  {eth:20s}: {len(real_paths):5d} real frames  |  {len(fake_paths):5d} fake frames")

        all_real.extend(real_paths)
        all_fake.extend(fake_paths)

    # Global cap (optional)
    np.random.shuffle(all_real)
    np.random.shuffle(all_fake)
    if max_real: all_real = all_real[:max_real]
    if max_fake: all_fake = all_fake[:max_fake]

    print(f"\n  Extracting features for {split_name}...")
    X_real, ok_real = extract_batch(all_real, "real")
    X_fake, ok_fake = extract_batch(all_fake, "fake")

    X = np.vstack([X_real, X_fake])
    y = np.array([0]*len(X_real) + [1]*len(X_fake))
    paths = ok_real + ok_fake

    print(f"  → {split_name}: {len(X_real)} real  |  {len(X_fake)} fake  |  {len(X)} total\n")
    return X, y, paths, ok_real, ok_fake, stats

# ─────────────────────────────────────────────
#  Visualization
# ─────────────────────────────────────────────

DARK   = "#0d0d0d"
PANEL  = "#141414"
TEAL   = "#00e5c0"
PINK   = "#ff4b6e"
PURPLE = "#7c4dff"
GRID   = "#2a2a2a"
TEXT   = "#e8e8e8"

def style_ax(ax, title=""):
    ax.set_facecolor(PANEL)
    ax.tick_params(colors=TEXT, labelsize=8)
    ax.xaxis.label.set_color(TEXT)
    ax.yaxis.label.set_color(TEXT)
    for sp in ax.spines.values():
        sp.set_color("#333")
    if title:
        ax.set_title(title, color=TEXT, fontsize=10, fontweight="bold", pad=8)
    ax.grid(True, color=GRID, lw=0.5, alpha=0.7)

def plot_roc(ax, y_true, y_prob, label, color, ls="-"):
    fpr, tpr, _ = roc_curve(y_true, y_prob)
    auc = roc_auc_score(y_true, y_prob)
    ax.plot(fpr, tpr, color=color, lw=2, ls=ls, label=f"{label}  AUC={auc:.3f}")
    ax.fill_between(fpr, tpr, alpha=0.08, color=color)
    return auc

def plot_cm(ax, cm, title, border_color):
    cm_n = cm.astype(float) / cm.sum(axis=1, keepdims=True)
    ax.imshow(cm_n, cmap="magma", vmin=0, vmax=1)
    ax.set_xticks([0,1]); ax.set_yticks([0,1])
    ax.set_xticklabels(["Real","Fake"], color=TEXT, fontsize=8)
    ax.set_yticklabels(["Real","Fake"], color=TEXT, fontsize=8, rotation=90, va="center")
    for (i,j), v in np.ndenumerate(cm):
        ax.text(j, i, f"{v}\n({cm_n[i,j]:.1%})",
                ha="center", va="center", color="white", fontsize=8, fontweight="bold")
    ax.set_xlabel("Predicted", color=TEXT, fontsize=8)
    ax.set_ylabel("Actual", color=TEXT, fontsize=8)
    ax.set_title(title, color=border_color, fontsize=10, fontweight="bold", pad=8)
    for sp in ax.spines.values():
        sp.set_color(border_color); sp.set_linewidth(2)

def generate_report(
        # Train
        X_train, y_train, paths_real_tr, paths_fake_tr,
        # Test sets
        X_test_am, y_test_am, X_test_eu, y_test_eu,
        # Predictions
        clf_pipeline,
        train_stats, test_am_stats, test_eu_stats,
        out_dir):

    y_prob_tr  = clf_pipeline.predict_proba(X_train)[:,1]
    y_pred_tr  = clf_pipeline.predict(X_train)

    y_prob_am  = clf_pipeline.predict_proba(X_test_am)[:,1]
    y_pred_am  = clf_pipeline.predict(X_test_am)

    y_prob_eu  = clf_pipeline.predict_proba(X_test_eu)[:,1]
    y_pred_eu  = clf_pipeline.predict(X_test_eu)

    cm_am = confusion_matrix(y_test_am, y_pred_am)
    cm_eu = confusion_matrix(y_test_eu, y_pred_eu)

    # ── spectral profiles
    def mean_std(X, y, label):
        feats = X[y == (0 if label=="real" else 1)]
        return feats.mean(0), feats.std(0)

    freqs = np.linspace(0, 1, N_BINS)
    mr_tr, sr_tr = mean_std(X_train, y_train, "real")
    mf_tr, sf_tr = mean_std(X_train, y_train, "fake")

    # ─── Figure ───────────────────────────────
    fig = plt.figure(figsize=(22, 18), facecolor=DARK)
    fig.patch.set_facecolor(DARK)
    gs = gridspec.GridSpec(3, 4, figure=fig, hspace=0.48, wspace=0.38,
                           top=0.93, bottom=0.05, left=0.06, right=0.97)

    fig.text(0.5, 0.97,
             "Cross-Ethnic Spectral Deepfake Detection  ·  arXiv:2003.01826",
             ha="center", va="top", color=TEXT,
             fontsize=15, fontweight="bold", family="monospace")
    fig.text(0.5, 0.945,
             "Train: African + East Asian + South Asian  →  Test: Caucasian American & European (zero-shot)",
             ha="center", va="top", color="#888", fontsize=10, family="monospace")

    # ── Row 0: spectral profiles ──
    ax0 = fig.add_subplot(gs[0, :2])
    sm_r = uniform_filter1d(mr_tr, 3)
    sm_f = uniform_filter1d(mf_tr, 3)
    ax0.fill_between(freqs, sm_r-sr_tr, sm_r+sr_tr, alpha=0.18, color=TEAL)
    ax0.fill_between(freqs, sm_f-sf_tr, sm_f+sf_tr, alpha=0.18, color=PINK)
    ax0.plot(freqs, sm_r, color=TEAL, lw=2, label="Real (train)")
    ax0.plot(freqs, sm_f, color=PINK, lw=2, label="Fake (train)")
    ax0.set_xlabel("Normalized Frequency")
    ax0.set_ylabel("Normalized Log Power")
    style_ax(ax0, "Mean Azimuthal Spectral Profile (Training Set)")
    ax0.legend(facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT, fontsize=9)

    ax1 = fig.add_subplot(gs[0, 2:])
    diff = sm_f - sm_r
    ax1.axhline(0, color="#555", lw=1, ls="--")
    ax1.fill_between(freqs, diff, 0, where=(diff>0), alpha=0.55, color=PINK, label="Fake > Real")
    ax1.fill_between(freqs, diff, 0, where=(diff<0), alpha=0.55, color=TEAL, label="Real > Fake")
    ax1.plot(freqs, diff, color="white", lw=1, alpha=0.5)
    ax1.set_xlabel("Normalized Frequency")
    ax1.set_ylabel("Δ Log Power (Fake − Real)")
    style_ax(ax1, "Spectral Difference: Fake − Real (Training Set)")
    ax1.legend(facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT, fontsize=9)

    # ── Row 1: ROC curves + confusion matrices ──
    ax_roc = fig.add_subplot(gs[1, :2])
    plot_roc(ax_roc, y_train,   y_prob_tr,  "Train (in-dist)",       "#aaaaaa", ls="--")
    plot_roc(ax_roc, y_test_am, y_prob_am,  "Test: Caucasian-Amer.", "#ffa726")
    plot_roc(ax_roc, y_test_eu, y_prob_eu,  "Test: Caucasian-Eur.",  PURPLE)
    ax_roc.plot([0,1],[0,1],"--",color="#444",lw=1)
    ax_roc.set_xlabel("False Positive Rate")
    ax_roc.set_ylabel("True Positive Rate")
    style_ax(ax_roc, "ROC Curves — Train vs. Zero-Shot Test")
    ax_roc.legend(facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT, fontsize=9,
                  loc="lower right")
    ax_roc.set_xlim([0,1]); ax_roc.set_ylim([0,1.02])

    ax_cm_am = fig.add_subplot(gs[1, 2])
    ax_cm_am.set_facecolor(PANEL)
    plot_cm(ax_cm_am, cm_am, "Caucasian American", "#ffa726")

    ax_cm_eu = fig.add_subplot(gs[1, 3])
    ax_cm_eu.set_facecolor(PANEL)
    plot_cm(ax_cm_eu, cm_eu, "Caucasian European", PURPLE)

    # ── Row 2: summary table + per-ethnicity bars ──
    ax_bar = fig.add_subplot(gs[2, :2])
    ax_bar.set_facecolor(PANEL)

    eth_labels = list(train_stats.keys())
    real_counts = [train_stats[e]["real_raw"] for e in eth_labels]
    fake_counts = [train_stats[e]["fake_raw"] for e in eth_labels]
    x = np.arange(len(eth_labels))
    w = 0.35
    ax_bar.bar(x - w/2, real_counts, w, color=TEAL, alpha=0.85, label="Real frames")
    ax_bar.bar(x + w/2, fake_counts, w, color=PINK, alpha=0.85, label="Fake frames")
    ax_bar.set_xticks(x)
    ax_bar.set_xticklabels(eth_labels, color=TEXT, fontsize=9, rotation=15)
    ax_bar.set_ylabel("Frame count", color=TEXT)
    style_ax(ax_bar, "Training Frame Counts by Ethnicity")
    ax_bar.legend(facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT, fontsize=9)

    # Metrics summary text box
    ax_txt = fig.add_subplot(gs[2, 2:])
    ax_txt.set_facecolor(PANEL)
    ax_txt.axis("off")
    for sp in ax_txt.spines.values():
        sp.set_color("#333")

    def fmt(y_t, y_p, y_pr, name):
        acc = accuracy_score(y_t, y_p)
        auc = roc_auc_score(y_t, y_pr)
        rep = classification_report(y_t, y_p, target_names=["Real","Fake"],
                                    output_dict=True)
        return (f"{name}\n"
                f"  Accuracy : {acc:.4f} ({acc*100:.2f}%)\n"
                f"  AUC      : {auc:.4f}\n"
                f"  F1-Real  : {rep['Real']['f1-score']:.4f}\n"
                f"  F1-Fake  : {rep['Fake']['f1-score']:.4f}\n"
                f"  Recall-R : {rep['Real']['recall']:.4f}\n"
                f"  Recall-F : {rep['Fake']['recall']:.4f}")

    summary = (
        "─── RESULTS SUMMARY ──────────────────────────\n\n"
        + fmt(y_train,   y_pred_tr,  y_prob_tr,  "● Train (African+EastAsian+SouthAsian)") + "\n\n"
        + fmt(y_test_am, y_pred_am,  y_prob_am,  "● Test  — Caucasian American  [zero-shot]") + "\n\n"
        + fmt(y_test_eu, y_pred_eu,  y_prob_eu,  "● Test  — Caucasian European  [zero-shot]")
    )
    ax_txt.text(0.04, 0.97, summary, transform=ax_txt.transAxes,
                va="top", ha="left", color=TEXT, fontsize=8.5,
                fontfamily="monospace",
                bbox=dict(facecolor="#1a1a1a", edgecolor="#444", boxstyle="round,pad=0.5"))

    fig.savefig(os.path.join(out_dir, "cross_ethnic_results.png"),
                dpi=150, bbox_inches="tight", facecolor=DARK)
    plt.close()
    print(f"  Saved → {out_dir}/cross_ethnic_results.png")

# ─────────────────────────────────────────────
#  Main
# ─────────────────────────────────────────────

def main():
    ap = argparse.ArgumentParser(
        description="Cross-ethnic spectral deepfake detector (arXiv:2003.01826)")
    ap.add_argument("--dataset",  required=True,
                    help="Root of FakeAVCeleb_faces with per-ethnicity subfolders")
    ap.add_argument("--max_real", type=int, default=None,
                    help="Cap total training real frames (default: unlimited)")
    ap.add_argument("--max_fake", type=int, default=None,
                    help="Cap total training fake frames (default: unlimited)")
    ap.add_argument("--out", default="cross_ethnic_output",
                    help="Output directory (default: cross_ethnic_output)")
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()

    np.random.seed(args.seed)
    os.makedirs(args.out, exist_ok=True)

    print("\n📁 Scanning dataset structure...")
    eth_dirs = find_ethnicity_dirs(args.dataset)
    if not eth_dirs:
        print(f"❌ No recognised ethnicity folders found under: {args.dataset}")
        print("   Expected names like: African, EastAsian, SouthAsian, "
              "CaucasianAmerican, CaucasianEuropean")
        sys.exit(1)
    for k, v in sorted(eth_dirs.items()):
        print(f"   {k:25s} → {v}")

    # ── Training data ──
    print("\n🏋  Loading TRAINING data (African + EastAsian + SouthAsian)...")
    X_tr, y_tr, _, ok_real_tr, ok_fake_tr, train_stats = load_split(
        eth_dirs, TRAIN_ETHNICITIES, "Train",
        real_all_frames=True,
        max_real=args.max_real, max_fake=args.max_fake
    )

    # ── Test: Caucasian American ──
    print("🧪  Loading TEST data — Caucasian American...")
    X_am, y_am, _, _, _, test_am_stats = load_split(
        eth_dirs, {"CaucasianAmerican"}, "CaucasianAmerican",
        real_all_frames=True,
        max_real=None, max_fake=None
    )

    # ── Test: Caucasian European ──
    print("🧪  Loading TEST data — Caucasian European...")
    X_eu, y_eu, _, _, _, test_eu_stats = load_split(
        eth_dirs, {"CaucasianEuropean"}, "CaucasianEuropean",
        real_all_frames=True,
        max_real=None, max_fake=None
    )

    # ── Train classifier ──
    print("🔬 Training SVM classifier on training ethnicities...")
    clf = Pipeline([
        ("scaler", StandardScaler()),
        ("svm",    SVC(kernel="rbf", C=10, probability=True, random_state=42))
    ])
    clf.fit(X_tr, y_tr)

    # ── Evaluate ──
    def evaluate(X, y, name):
        y_pred = clf.predict(X)
        y_prob = clf.predict_proba(X)[:,1]
        acc = accuracy_score(y, y_pred)
        auc = roc_auc_score(y, y_prob)
        rep = classification_report(y, y_pred, target_names=["Real","Fake"])
        cm  = confusion_matrix(y, y_pred)
        print(f"\n{'='*56}")
        print(f" {name}")
        print(f"{'='*56}")
        print(f"  Accuracy : {acc:.4f}  ({acc*100:.2f}%)")
        print(f"  AUC      : {auc:.4f}")
        print(rep)
        return {"accuracy": float(acc), "auc": float(auc),
                "confusion_matrix": cm.tolist()}

    res_tr = evaluate(X_tr, y_tr, "TRAIN — African + EastAsian + SouthAsian")
    res_am = evaluate(X_am, y_am, "TEST  — Caucasian American [zero-shot]")
    res_eu = evaluate(X_eu, y_eu, "TEST  — Caucasian European [zero-shot]")

    # Save metrics
    metrics = {
        "training":             res_tr,
        "test_caucasian_american": res_am,
        "test_caucasian_european": res_eu,
    }
    with open(os.path.join(args.out, "metrics.json"), "w") as f:
        json.dump(metrics, f, indent=2)
    print(f"\n📄 metrics.json saved → {args.out}/")

    # ── Visualize ──
    print("\n🎨 Generating visualizations...")
    generate_report(
        X_tr, y_tr, ok_real_tr, ok_fake_tr,
        X_am, y_am, X_eu, y_eu,
        clf,
        train_stats, test_am_stats, test_eu_stats,
        args.out
    )

    print(f"\n✅ Done! All outputs in: {args.out}/")


if __name__ == "__main__":
    main()
