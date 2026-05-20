"""
Spectral Deepfake Detector — Cross-Ethnic Generalization Experiment
Based on: arXiv:2003.01826  "Watch your Up-Convolution"

DATASET STRUCTURE (FakeAVCeleb_faces):
  FakeAVCeleb_faces/
    RealVideo-RealAudio/
      African/          id00001/ frame_0001.jpg ...
      EastAsian/
      SouthAsian/
      CaucasianAmerican/
      CaucasianEuropean/
    FakeVideo-FakeAudio/
      African/  ...  (same ethnicity subfolders)
    FakeVideo-RealAudio/
      African/  ...

TRAINING  — African + EastAsian + SouthAsian
  Real  : RealVideo-RealAudio   → all 32 frames per video
  Fake  : FakeVideo-FakeAudio + FakeVideo-RealAudio → 1 frame per video

TESTING   — zero-shot on unseen ethnicities
  CaucasianAmerican  (reported separately)
  CaucasianEuropean  (reported separately)

Usage:
    python spectral_deepfake_detector_v3.py --dataset /path/to/FakeAVCeleb_faces
"""

import os, sys, re, json, argparse, warnings
warnings.filterwarnings("ignore")

import numpy as np
from pathlib import Path
from PIL import Image
import cv2
from collections import defaultdict

from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.metrics import (accuracy_score, roc_auc_score,
                              classification_report, confusion_matrix, roc_curve)

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from scipy.ndimage import uniform_filter1d

# ─────────────────────────────────────────────────────────────────────────────
#  Constants
# ─────────────────────────────────────────────────────────────────────────────

IMG_EXTS = {".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".webp"}
IMG_SIZE  = 128
N_BINS    = 64

# ── Top-level category folder fuzzy-matching ──────────────────────────────────
CAT_REAL_KEYS = {"realvideorealaudio", "realvideo-realaudio", "real"}
CAT_FFA_KEYS  = {"fakevideofakeaudio", "fakevideo-fakeaudio"}
CAT_FRA_KEYS  = {"fakevideorealaudio", "fakevideo-realaudio"}

# ── Ethnicity subfolder fuzzy-matching ────────────────────────────────────────
ETH_MAP = {
    "african":               "African",
    "black":                 "African",
    "eastasian":             "EastAsian",
    "east_asian":            "EastAsian",
    "eastasian(east)":       "EastAsian",
    "asian(east)":           "EastAsian",
    "asian-east":            "EastAsian",
    "southasian":            "SouthAsian",
    "south_asian":           "SouthAsian",
    "asian(south)":          "SouthAsian",
    "asian-south":           "SouthAsian",
    "caucasianamerican":     "CaucasianAmerican",
    "caucasian_american":    "CaucasianAmerican",
    "caucasian-american":    "CaucasianAmerican",
    "caucasian(american)":   "CaucasianAmerican",
    "caucasianeuropean":     "CaucasianEuropean",
    "caucasian_european":    "CaucasianEuropean",
    "caucasian-european":    "CaucasianEuropean",
    "caucasian(european)":   "CaucasianEuropean",
}

TRAIN_ETH = {"African", "EastAsian", "SouthAsian"}
TEST_ETH  = {"CaucasianAmerican", "CaucasianEuropean"}


def norm(s):
    """Lowercase, strip spaces/hyphens/underscores."""
    return re.sub(r"[\s_\-]", "", s).lower()


# ─────────────────────────────────────────────────────────────────────────────
#  Spectral feature extraction  (arXiv:2003.01826 §3)
# ─────────────────────────────────────────────────────────────────────────────

def azimuthal_average(ps):
    h, w   = ps.shape
    cy, cx = h // 2, w // 2
    y, x   = np.ogrid[:h, :w]
    r      = np.sqrt((x - cx)**2 + (y - cy)**2).astype(int)
    max_r  = min(cx, cy)
    avg    = np.zeros(max_r)
    for i in range(max_r):
        m = r == i
        if m.any():
            avg[i] = ps[m].mean()
    return avg


def extract_feature(image_path):
    try:
        img  = Image.open(image_path).convert("RGB")
        img  = img.resize((IMG_SIZE, IMG_SIZE), Image.LANCZOS)
        gray = cv2.cvtColor(np.array(img), cv2.COLOR_RGB2GRAY).astype(np.float32)
        fft  = np.fft.fftshift(np.fft.fft2(gray))
        lps  = np.log1p(np.abs(fft) ** 2)
        rad  = azimuthal_average(lps)
        bins = np.linspace(0, len(rad) - 1, N_BINS)
        feat = np.interp(bins, np.arange(len(rad)), rad)
        n    = np.linalg.norm(feat)
        return feat / n if n > 0 else feat
    except Exception:
        return None


def extract_batch(paths, tag):
    feats, ok = [], []
    total = len(paths)
    for i, p in enumerate(paths):
        if i % 500 == 0:
            print(f"    [{tag}] {i}/{total}", end="\r", flush=True)
        f = extract_feature(p)
        if f is not None:
            feats.append(f)
            ok.append(p)
    print(f"    [{tag}] {len(feats)}/{total} OK   ")
    return np.array(feats) if feats else np.empty((0, N_BINS)), ok


# ─────────────────────────────────────────────────────────────────────────────
#  Dataset discovery  (category-first layout)
# ─────────────────────────────────────────────────────────────────────────────

def scan_root(dataset_root):
    """
    Returns:
        cat_dirs = {
            'real':     Path,
            'fake_ffa': Path,
            'fake_fra': Path,
        }
    """
    root     = Path(dataset_root)
    cat_dirs = {"real": None, "fake_ffa": None, "fake_fra": None}

    for d in root.iterdir():
        if not d.is_dir():
            continue
        k = norm(d.name)
        if k in CAT_REAL_KEYS:
            cat_dirs["real"]     = d
        elif k in CAT_FFA_KEYS:
            cat_dirs["fake_ffa"] = d
        elif k in CAT_FRA_KEYS:
            cat_dirs["fake_fra"] = d

    missing = [k for k, v in cat_dirs.items() if v is None]
    if missing:
        print(f"  ⚠  Could not find category folders: {missing}")
        print(f"     Folders found: {[d.name for d in root.iterdir() if d.is_dir()]}")
    else:
        print(f"  Real  : {cat_dirs['real'].name}")
        print(f"  FFA   : {cat_dirs['fake_ffa'].name}")
        print(f"  FRA   : {cat_dirs['fake_fra'].name}")

    return cat_dirs


def get_eth_paths(cat_dir):
    """
    Within a category folder, find {canonical_eth: Path} for all ethnicities.
    """
    result = {}
    if cat_dir is None:
        return result
    for d in cat_dir.iterdir():
        if not d.is_dir():
            continue
        key = ETH_MAP.get(norm(d.name))
        if key:
            result[key] = d
        else:
            print(f"  ⚠  Unrecognised ethnicity folder: {d.name!r}  (skipped)")
    return result


def get_video_groups(folder):
    """Group image paths by their immediate parent (= one video subfolder)."""
    groups = defaultdict(list)
    for root, dirs, files in os.walk(folder):
        for f in files:
            if Path(f).suffix.lower() in IMG_EXTS:
                groups[root].append(os.path.join(root, f))
    for k in groups:
        groups[k].sort()
    return groups


def collect_paths(cat_dir, ethnicities, n_frames_per_video):
    """
    For the given category folder and list of ethnicities,
    collect image paths (n_frames_per_video per video, sorted).
    Returns {eth: [paths]}, total_count.
    """
    eth_paths = get_eth_paths(cat_dir)
    result    = {}
    for eth in ethnicities:
        if eth not in eth_paths:
            print(f"  ⚠  {eth} not found in {cat_dir.name}")
            result[eth] = []
            continue
        vg    = get_video_groups(eth_paths[eth])
        paths = []
        for frames in vg.values():
            paths.extend(frames[:n_frames_per_video])
        result[eth] = paths
    return result


# ─────────────────────────────────────────────────────────────────────────────
#  Build feature matrix for one ethnicity group
# ─────────────────────────────────────────────────────────────────────────────

def build_split(cat_dirs, ethnicities, split_name,
                real_frames=32, fake_frames=1):
    """
    Returns X, y, ok_real_paths, ok_fake_paths, per_eth_stats.
    """
    # ── real paths (from RealVideo-RealAudio) ──
    real_by_eth = collect_paths(cat_dirs["real"], ethnicities, real_frames)

    # ── fake paths (FFA + FRA, 1 frame/video each) ──
    ffa_by_eth  = collect_paths(cat_dirs["fake_ffa"], ethnicities, fake_frames) \
                  if cat_dirs["fake_ffa"] else {e: [] for e in ethnicities}
    fra_by_eth  = collect_paths(cat_dirs["fake_fra"], ethnicities, fake_frames) \
                  if cat_dirs["fake_fra"] else {e: [] for e in ethnicities}

    all_real, all_fake = [], []
    stats = {}
    for eth in sorted(ethnicities):
        r = real_by_eth.get(eth, [])
        f = ffa_by_eth.get(eth, []) + fra_by_eth.get(eth, [])
        print(f"    {eth:22s}: {len(r):6d} real frames  |  {len(f):6d} fake frames")
        stats[eth] = {"real": len(r), "fake": len(f)}
        all_real.extend(r)
        all_fake.extend(f)

    print(f"\n  Extracting features — {split_name} ...")
    X_real, ok_real = extract_batch(all_real, "real")
    X_fake, ok_fake = extract_batch(all_fake, "fake")

    X = np.vstack([X_real, X_fake])
    y = np.array([0] * len(ok_real) + [1] * len(ok_fake))
    print(f"  → {split_name}: {len(ok_real)} real | {len(ok_fake)} fake | {len(X)} total\n")
    return X, y, ok_real, ok_fake, stats


# ─────────────────────────────────────────────────────────────────────────────
#  Visualization
# ─────────────────────────────────────────────────────────────────────────────

DARK   = "#0d0d0d"
PANEL  = "#141414"
TEAL   = "#00e5c0"
PINK   = "#ff4b6e"
ORANGE = "#ffa726"
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
    auc          = roc_auc_score(y_true, y_prob)
    ax.plot(fpr, tpr, color=color, lw=2, ls=ls, label=f"{label}  AUC={auc:.3f}")
    ax.fill_between(fpr, tpr, alpha=0.07, color=color)
    return auc


def plot_cm(ax, cm, title, border_color):
    cm_n = cm.astype(float) / cm.sum(axis=1, keepdims=True)
    ax.imshow(cm_n, cmap="magma", vmin=0, vmax=1)
    ax.set_xticks([0, 1]); ax.set_yticks([0, 1])
    ax.set_xticklabels(["Real", "Fake"], color=TEXT, fontsize=8)
    ax.set_yticklabels(["Real", "Fake"], color=TEXT, fontsize=8,
                       rotation=90, va="center")
    for (i, j), v in np.ndenumerate(cm):
        ax.text(j, i, f"{v}\n({cm_n[i,j]:.1%})",
                ha="center", va="center", color="white",
                fontsize=8, fontweight="bold")
    ax.set_xlabel("Predicted", color=TEXT, fontsize=8)
    ax.set_ylabel("Actual",    color=TEXT, fontsize=8)
    ax.set_title(title, color=border_color, fontsize=10, fontweight="bold", pad=8)
    for sp in ax.spines.values():
        sp.set_color(border_color); sp.set_linewidth(2)


def generate_figure(
        X_tr, y_tr,
        X_am, y_am,
        X_eu, y_eu,
        clf,
        train_stats, test_am_stats, test_eu_stats,
        out_path):

    yp_tr = clf.predict_proba(X_tr)[:, 1]
    yd_tr = clf.predict(X_tr)
    yp_am = clf.predict_proba(X_am)[:, 1]
    yd_am = clf.predict(X_am)
    yp_eu = clf.predict_proba(X_eu)[:, 1]
    yd_eu = clf.predict(X_eu)

    cm_am = confusion_matrix(y_am, yd_am)
    cm_eu = confusion_matrix(y_eu, yd_eu)

    freqs  = np.linspace(0, 1, N_BINS)
    mr     = uniform_filter1d(X_tr[y_tr == 0].mean(0), 3)
    mf     = uniform_filter1d(X_tr[y_tr == 1].mean(0), 3)
    sr, sf = X_tr[y_tr == 0].std(0), X_tr[y_tr == 1].std(0)

    fig = plt.figure(figsize=(22, 18), facecolor=DARK)
    fig.patch.set_facecolor(DARK)
    gs  = gridspec.GridSpec(3, 4, figure=fig, hspace=0.48, wspace=0.38,
                            top=0.93, bottom=0.05, left=0.06, right=0.97)

    fig.text(0.5, 0.972,
             "Cross-Ethnic Spectral Deepfake Detection  ·  arXiv:2003.01826",
             ha="center", color=TEXT, fontsize=15, fontweight="bold",
             family="monospace")
    fig.text(0.5, 0.947,
             "Train: African + East Asian + South Asian   ▶   "
             "Test (zero-shot): Caucasian American & European",
             ha="center", color="#888", fontsize=10, family="monospace")

    # ── Spectral profile ──────────────────────────────────────────────────────
    ax0 = fig.add_subplot(gs[0, :2])
    ax0.fill_between(freqs, mr - sr, mr + sr, alpha=0.15, color=TEAL)
    ax0.fill_between(freqs, mf - sf, mf + sf, alpha=0.15, color=PINK)
    ax0.plot(freqs, mr, color=TEAL, lw=2, label="Real (train)")
    ax0.plot(freqs, mf, color=PINK, lw=2, label="Fake (train)")
    ax0.set_xlabel("Normalized Frequency")
    ax0.set_ylabel("Normalized Log Power")
    style_ax(ax0, "Mean Azimuthal Spectral Profile  (Training Set)")
    ax0.legend(facecolor="#1e1e1e", edgecolor="#444",
               labelcolor=TEXT, fontsize=9)

    # ── Spectral difference ───────────────────────────────────────────────────
    ax1    = fig.add_subplot(gs[0, 2:])
    diff   = mf - mr
    ax1.axhline(0, color="#555", lw=1, ls="--")
    ax1.fill_between(freqs, diff, 0, where=(diff > 0), alpha=0.55,
                     color=PINK,  label="Fake > Real")
    ax1.fill_between(freqs, diff, 0, where=(diff < 0), alpha=0.55,
                     color=TEAL,  label="Real > Fake")
    ax1.plot(freqs, diff, color="white", lw=1, alpha=0.45)
    ax1.set_xlabel("Normalized Frequency")
    ax1.set_ylabel("Δ Log Power  (Fake − Real)")
    style_ax(ax1, "Spectral Difference: Fake − Real  (Training Set)")
    ax1.legend(facecolor="#1e1e1e", edgecolor="#444",
               labelcolor=TEXT, fontsize=9)

    # ── ROC curves ────────────────────────────────────────────────────────────
    ax_roc = fig.add_subplot(gs[1, :2])
    plot_roc(ax_roc, y_tr, yp_tr, "Train (in-dist)",         "#888",   ls="--")
    plot_roc(ax_roc, y_am, yp_am, "Test: Caucasian-American", ORANGE)
    plot_roc(ax_roc, y_eu, yp_eu, "Test: Caucasian-European", PURPLE)
    ax_roc.plot([0, 1], [0, 1], "--", color="#444", lw=1)
    ax_roc.set_xlabel("False Positive Rate")
    ax_roc.set_ylabel("True Positive Rate")
    style_ax(ax_roc, "ROC Curves — Train vs Zero-Shot Test")
    ax_roc.legend(facecolor="#1e1e1e", edgecolor="#444",
                  labelcolor=TEXT, fontsize=9, loc="lower right")
    ax_roc.set_xlim([0, 1]); ax_roc.set_ylim([0, 1.02])

    # ── Confusion matrices ────────────────────────────────────────────────────
    ax_cm_am = fig.add_subplot(gs[1, 2])
    ax_cm_am.set_facecolor(PANEL)
    plot_cm(ax_cm_am, cm_am, "Test: Caucasian American", ORANGE)

    ax_cm_eu = fig.add_subplot(gs[1, 3])
    ax_cm_eu.set_facecolor(PANEL)
    plot_cm(ax_cm_eu, cm_eu, "Test: Caucasian European", PURPLE)

    # ── Frame-count bar chart ─────────────────────────────────────────────────
    ax_bar  = fig.add_subplot(gs[2, :2])
    ax_bar.set_facecolor(PANEL)
    all_eth = sorted(set(list(train_stats) + list(test_am_stats) + list(test_eu_stats)))
    merged  = {}
    for e in all_eth:
        r = (train_stats.get(e) or test_am_stats.get(e) or
             test_eu_stats.get(e) or {}).get("real", 0)
        f = (train_stats.get(e) or test_am_stats.get(e) or
             test_eu_stats.get(e) or {}).get("fake", 0)
        merged[e] = (r, f)

    x      = np.arange(len(all_eth))
    w      = 0.35
    colors_r = [TEAL if e in TRAIN_ETH else "#444" for e in all_eth]
    colors_f = [PINK if e in TRAIN_ETH else "#666" for e in all_eth]
    for i, (e, (r, f)) in enumerate(merged.items()):
        ax_bar.bar(i - w/2, r, w, color=colors_r[i], alpha=0.85)
        ax_bar.bar(i + w/2, f, w, color=colors_f[i], alpha=0.85)
    ax_bar.set_xticks(x)
    ax_bar.set_xticklabels(all_eth, color=TEXT, fontsize=8, rotation=20, ha="right")
    ax_bar.set_ylabel("Frame count", color=TEXT)
    # legend proxies
    from matplotlib.patches import Patch
    ax_bar.legend(handles=[
        Patch(facecolor=TEAL, label="Real — train ethnicity"),
        Patch(facecolor=PINK, label="Fake — train ethnicity"),
        Patch(facecolor="#444", label="Real — test ethnicity"),
        Patch(facecolor="#666", label="Fake — test ethnicity"),
    ], facecolor="#1e1e1e", edgecolor="#444", labelcolor=TEXT, fontsize=8)
    style_ax(ax_bar, "Frame Counts by Ethnicity (bright = train, dim = test)")

    # ── Metrics summary ───────────────────────────────────────────────────────
    ax_txt = fig.add_subplot(gs[2, 2:])
    ax_txt.set_facecolor(PANEL)
    ax_txt.axis("off")

    def fmt(yt, yp, ypr, name):
        acc = accuracy_score(yt, yp)
        auc = roc_auc_score(yt, ypr)
        d   = classification_report(yt, yp, target_names=["Real","Fake"],
                                    output_dict=True, zero_division=0)
        return (f"{name}\n"
                f"  Accuracy  {acc:.4f}  ({acc*100:.2f}%)\n"
                f"  ROC-AUC   {auc:.4f}\n"
                f"  F1  Real  {d['Real']['f1-score']:.4f}   "
                f"Fake  {d['Fake']['f1-score']:.4f}\n"
                f"  Rec Real  {d['Real']['recall']:.4f}   "
                f"Fake  {d['Fake']['recall']:.4f}")

    lines = ("─── RESULTS SUMMARY ────────────────────────────────\n\n"
             + fmt(y_tr, yd_tr, yp_tr,
                   "● Train  African + EastAsian + SouthAsian") + "\n\n"
             + fmt(y_am, yd_am, yp_am,
                   "● Test   Caucasian American  [zero-shot]") + "\n\n"
             + fmt(y_eu, yd_eu, yp_eu,
                   "● Test   Caucasian European  [zero-shot]"))

    ax_txt.text(0.04, 0.97, lines, transform=ax_txt.transAxes,
                va="top", ha="left", color=TEXT, fontsize=8.5,
                fontfamily="monospace",
                bbox=dict(facecolor="#1a1a1a", edgecolor="#444",
                          boxstyle="round,pad=0.5"))

    fig.savefig(out_path, dpi=150, bbox_inches="tight", facecolor=DARK)
    plt.close()
    print(f"  Saved → {out_path}")


# ─────────────────────────────────────────────────────────────────────────────
#  Main
# ─────────────────────────────────────────────────────────────────────────────

def main():
    ap = argparse.ArgumentParser(
        description="Cross-ethnic spectral deepfake detector  (arXiv:2003.01826)")
    ap.add_argument("--dataset", required=True,
                    help="Root of FakeAVCeleb_faces/  "
                         "(contains RealVideo-RealAudio/, FakeVideo-FakeAudio/, …)")
    ap.add_argument("--out", default="cross_ethnic_output",
                    help="Output directory  (default: cross_ethnic_output)")
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()

    np.random.seed(args.seed)
    os.makedirs(args.out, exist_ok=True)

    print("\n📁  Scanning dataset root ...")
    cat_dirs = scan_root(args.dataset)
    if cat_dirs["real"] is None:
        print("❌  RealVideo-RealAudio folder not found. Aborting.")
        sys.exit(1)

    # ── Training split ──────────────────────────────────────────────────────
    print("\n🏋  TRAINING split  (African + EastAsian + SouthAsian)")
    X_tr, y_tr, ok_r_tr, ok_f_tr, stats_tr = build_split(
        cat_dirs, TRAIN_ETH, "Train",
        real_frames=32, fake_frames=1
    )

    # ── Test: Caucasian American ─────────────────────────────────────────────
    print("🧪  TEST split — Caucasian American")
    X_am, y_am, _, _, stats_am = build_split(
        cat_dirs, {"CaucasianAmerican"}, "CaucasianAmerican",
        real_frames=32, fake_frames=1
    )

    # ── Test: Caucasian European ─────────────────────────────────────────────
    print("🧪  TEST split — Caucasian European")
    X_eu, y_eu, _, _, stats_eu = build_split(
        cat_dirs, {"CaucasianEuropean"}, "CaucasianEuropean",
        real_frames=32, fake_frames=1
    )

    # ── Train SVM ────────────────────────────────────────────────────────────
    print("🔬  Training RBF-SVM on training ethnicities ...")
    clf = Pipeline([
        ("scaler", StandardScaler()),
        ("svm",    SVC(kernel="rbf", C=10, probability=True, random_state=42))
    ])
    clf.fit(X_tr, y_tr)

    # ── Evaluate & print ─────────────────────────────────────────────────────
    metrics = {}
    for X, y, name, key in [
        (X_tr, y_tr, "TRAIN  —  African + EastAsian + SouthAsian", "train"),
        (X_am, y_am, "TEST   —  Caucasian American  [zero-shot]",  "test_caucasian_american"),
        (X_eu, y_eu, "TEST   —  Caucasian European  [zero-shot]",  "test_caucasian_european"),
    ]:
        yd = clf.predict(X)
        yp = clf.predict_proba(X)[:, 1]
        acc = accuracy_score(y, yd)
        auc = roc_auc_score(y, yp)
        print(f"\n{'='*60}")
        print(f"  {name}")
        print(f"{'='*60}")
        print(f"  Accuracy : {acc:.4f}  ({acc*100:.2f}%)")
        print(f"  AUC      : {auc:.4f}")
        print(classification_report(y, yd, target_names=["Real","Fake"],
                                    zero_division=0))
        metrics[key] = {
            "accuracy": float(acc), "auc": float(auc),
            "confusion_matrix": confusion_matrix(y, yd).tolist()
        }

    with open(os.path.join(args.out, "metrics.json"), "w") as f:
        json.dump(metrics, f, indent=2)
    print(f"\n📄  metrics.json  →  {args.out}/")

    # ── Visualize ────────────────────────────────────────────────────────────
    print("\n🎨  Generating figure ...")
    generate_figure(
        X_tr, y_tr, X_am, y_am, X_eu, y_eu,
        clf, stats_tr, stats_am, stats_eu,
        os.path.join(args.out, "cross_ethnic_results.png")
    )
    print(f"\n✅  Done!  Outputs → {args.out}/")


if __name__ == "__main__":
    main()
