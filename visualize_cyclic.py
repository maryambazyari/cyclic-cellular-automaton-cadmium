import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import re
from pathlib import Path

# ===== تنظیمات =====
csv_file = "out/cyclic_basic_log.csv"   # اسم فایل لاگ
grid_rows = 20
grid_cols = 20

# اگر خواستی بعداً برای لاگ‌های دیگر:
# csv_file = "out/cyclic_wrapped_log.csv"
# csv_file = "out/cyclic_stripes_log.csv"

# ===== خواندن فایل =====
df = pd.read_csv(csv_file, sep=";")

# فقط ردیف‌هایی که state دارند
df = df[df["data"].notna()].copy()

# استخراج phase از <0> / <1> / <2>
df["phase"] = df["data"].str.extract(r"<(\d+)>").astype(int)

# استخراج مختصات از (r,c)
coords = df["model_name"].str.extract(r"\((\d+),(\d+)\)")
df["row"] = coords[0].astype(int)
df["col"] = coords[1].astype(int)

# time را عددی کن
df["time"] = pd.to_numeric(df["time"], errors="coerce")

# همه زمان‌های یکتا
times = sorted(df["time"].dropna().unique())

# فولدر خروجی
output_dir = Path("visualization_output")
output_dir.mkdir(exist_ok=True)

# ===== تابع ساخت grid برای هر زمان =====
def build_grid(t):
    grid = [[0 for _ in range(grid_cols)] for _ in range(grid_rows)]
    sub = df[df["time"] == t]
    for _, row in sub.iterrows():
        r = int(row["row"])
        c = int(row["col"])
        p = int(row["phase"])
        if 0 <= r < grid_rows and 0 <= c < grid_cols:
            grid[r][c] = p
    return grid

# ===== ذخیره چند snapshot =====
snapshot_indices = [0, len(times)//2, len(times)-1]
snapshot_names = ["start", "middle", "end"]

for idx, name in zip(snapshot_indices, snapshot_names):
    t = times[idx]
    grid = build_grid(t)

    plt.figure(figsize=(6, 6))
    plt.imshow(grid, vmin=0, vmax=2)
    plt.colorbar(label="Cell State")
    plt.title(f"Cyclic Cellular Automaton - {name} (time={t})")
    plt.xlabel("Column")
    plt.ylabel("Row")
    plt.tight_layout()
    plt.savefig(output_dir / f"{name}.png", dpi=200)
    plt.close()

print("Saved snapshots: start.png, middle.png, end.png")

# ===== ساخت animation mp4 یا gif =====
fig, ax = plt.subplots(figsize=(6, 6))
img = ax.imshow(build_grid(times[0]), vmin=0, vmax=2)
cbar = plt.colorbar(img, ax=ax)
cbar.set_label("Cell State")

def update(frame_idx):
    t = times[frame_idx]
    grid = build_grid(t)
    img.set_data(grid)
    ax.set_title(f"Cyclic Cellular Automaton (time={t})")
    return [img]

ani = animation.FuncAnimation(fig, update, frames=len(times), interval=300, blit=False)

# اول mp4 را امتحان می‌کنیم، اگر نشد gif
try:
    ani.save(output_dir / "cyclic_animation.mp4", fps=3)
    print("Saved animation: cyclic_animation.mp4")
except Exception as e:
    print("MP4 save failed, trying GIF...")
    try:
        ani.save(output_dir / "cyclic_animation.gif", fps=3)
        print("Saved animation: cyclic_animation.gif")
    except Exception as e2:
        print("GIF save also failed.")
        print("Error 1:", e)
        print("Error 2:", e2)

plt.close()