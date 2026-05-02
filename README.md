# Cyclic Cellular Automaton Cell-DEVS Model

This repository contains a Cell-DEVS implementation of a cyclic cellular automaton using Cadmium.

## Repository Contents

- `main_cyclic.cpp`: main simulation program
- `include/cyclic_state.hpp`: state definition
- `include/cyclic_grid_cell.hpp`: grid cell transition rules
- `include/cyclic_coupled.hpp`: coupled Cell-DEVS lattice model
- `cyclic_config.json`: basic experiment
- `cyclic_config_wrapped.json`: wrapped-boundary experiment
- `cyclic_config_stripes.json`: stripe initialization experiment
- `run_basic.bat`: Windows script for the basic experiment
- `run_wrapped.bat`: Windows script for the wrapped-boundary experiment
- `run_stripes.bat`: Windows script for the stripe initialization experiment
- `run_basic.sh`: Linux script for the basic experiment
- `run_wrapped.sh`: Linux script for the wrapped-boundary experiment
- `run_stripes.sh`: Linux script for the stripe initialization experiment
- `logs/`: simulation log files
- `visualization_output/`: generated snapshots and animation outputs
- `videos/`: simulation video
- `external/nlohmann/json.hpp`: bundled JSON single-header dependency
- `external/cadmium_v2/`: bundled Cadmium headers
- `external/boost/`: bundled Boost headers
- `visualize_cyclic.py`: Python visualization script for snapshots and animation generation
- `cyclic_cellular_automaton_report.pdf`: final report
- `DEVSmodelsForm.pdf`: submission form

## Dependencies

This repository includes the required local header dependencies for:

- `nlohmann/json`
- bundled Cadmium headers
- bundled Boost headers

To build and run the project, the user needs:

- CMake 3.16 or newer
- Ninja or another supported build generator
- A C++17 compiler
- valid Cadmium and Boost include paths passed at CMake configuration time

To generate the visualization outputs, the following Python packages are also required:

- `pandas`
- `matplotlib`

These Python packages are only needed for visualization and animation generation. They are not required to build or run the main C++ simulation.

## Build Instructions

From the repository root:

```bash
cd ~/cyclic-cellular-automaton-cadmium
rm -rf out
mkdir out
cd out
cmake -G Ninja .. -DCADMIUM_V2_DIR=$HOME/assignment/IndoorHumiditySystem-DEVS/external/cadmium/include -DBOOST_DIR=$HOME/smart-fridge-temperature-control-devs/external/boost
cmake --build .
./main_cyclic ../cyclic_config.json 50
```

After building, the executable will be available at:

```bash
./out/main_cyclic
```

To run the basic experiment:

```bash
./out/main_cyclic ./cyclic_config.json 50
```

To run the wrapped-boundary experiment:

```bash
./out/main_cyclic ./cyclic_config_wrapped.json 50
```

To run the stripe initialization experiment:

```bash
./out/main_cyclic ./cyclic_config_stripes.json 50
```

## Execution Scripts

### `run_basic.bat`

This script removes any previous `out` directory, rebuilds the project using CMake and Ninja, executes the model using `cyclic_config.json` for 50 simulation time units, and copies the generated output log to `logs/cyclic_basic_log.csv`.

### `run_wrapped.bat`

This script removes any previous `out` directory, rebuilds the project using CMake and Ninja, executes the model using `cyclic_config_wrapped.json` for 50 simulation time units, and copies the generated output log to `logs/cyclic_wrapped_log.csv`.

### `run_stripes.bat`

This script removes any previous `out` directory, rebuilds the project using CMake and Ninja, executes the model using `cyclic_config_stripes.json` for 50 simulation time units, and copies the generated output log to `logs/cyclic_stripes_log.csv`.

### `run_basic.sh`

This Linux script removes any previous `out` directory, rebuilds the project using CMake and Ninja, executes the model using `cyclic_config.json` for 50 simulation time units, and copies the generated output log to `logs/cyclic_basic_log.csv`.

### `run_wrapped.sh`

This Linux script removes any previous `out` directory, rebuilds the project using CMake and Ninja, executes the model using `cyclic_config_wrapped.json` for 50 simulation time units, and copies the generated output log to `logs/cyclic_wrapped_log.csv`.

### `run_stripes.sh`

This Linux script removes any previous `out` directory, rebuilds the project using CMake and Ninja, executes the model using `cyclic_config_stripes.json` for 50 simulation time units, and copies the generated output log to `logs/cyclic_stripes_log.csv`.

## Output Files

The project produces:

- CSV log files in the `logs/` folder
- visualization images and animation outputs in `visualization_output/`
- video output in the `videos/` folder

## Visualization and Video

The visualization outputs were generated from the simulation log files after running the model. The process used the Python script `visualize_cyclic.py`, which reads the simulation CSV log, reconstructs the grid state at each recorded simulation time, generates representative snapshots, and produces an animation of the cyclic cellular automaton evolution.

### Visualization Workflow

The visualization process was completed after the simulation had already been built and executed successfully. First, the C++ model was run to generate CSV log data. Then the Python visualization script was executed separately to process the log data and create the images and animation outputs.

The script uses the following Python libraries:

- `pandas` for reading and processing the CSV log file
- `matplotlib.pyplot` for plotting the grid states
- `matplotlib.animation` for generating the animation
- `pathlib` for handling output folders and file saving

### Input Used for Visualization

The visualization script reads a CSV log file generated by the simulation. In the current script, the default input is:

```python
csv_file = "out/cyclic_basic_log.csv"
```

This means the script expects the simulation log to be available in the `out/` directory. If the log file is stored in a different location, such as `logs/`, the path inside `visualize_cyclic.py` must be updated before running the script.

### What the Visualization Script Does

The `visualize_cyclic.py` script performs the following steps:

1. Reads the CSV simulation log using `pandas`
2. Filters the rows containing valid cell-state data
3. Extracts the cell state values from entries such as `<0>`, `<1>`, and `<2>`
4. Extracts the grid coordinates from the model names such as `(row,col)`
5. Collects all unique simulation times
6. Reconstructs the full 20 × 20 grid for each simulation time
7. Saves representative snapshots:
   - `start.png`
   - `middle.png`
   - `end.png`
8. Generates an animation of the model evolution over time

### Visualization Script

The script used for creating the snapshots and animation is:

```python
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import re
from pathlib import Path

# ===== Settings =====
csv_file = "out/cyclic_basic_log.csv"
grid_rows = 20
grid_cols = 20

# Optional alternatives:
# csv_file = "out/cyclic_wrapped_log.csv"
# csv_file = "out/cyclic_stripes_log.csv"

# ===== Read CSV =====
df = pd.read_csv(csv_file, sep=";")

# Keep only rows with valid state data
df = df[df["data"].notna()].copy()

# Extract phase from <0> / <1> / <2>
df["phase"] = df["data"].str.extract(r"<(\d+)>").astype(int)

# Extract coordinates from (r,c)
coords = df["model_name"].str.extract(r"\((\d+),(\d+)\)")
df["row"] = coords[0].astype(int)
df["col"] = coords[1].astype(int)

# Convert time to numeric
df["time"] = pd.to_numeric(df["time"], errors="coerce")

# All unique times
times = sorted(df["time"].dropna().unique())

# Output folder
output_dir = Path("visualization_output")
output_dir.mkdir(exist_ok=True)

# ===== Build grid for each time =====
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

# ===== Save snapshots =====
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

# ===== Create animation =====
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

# First try MP4, then GIF
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
```

### How to Run the Visualization Script

The visualization script was run from the repository root after the simulation output had already been generated.

Run:

```bash
python3 visualize_cyclic.py
```

If `pandas` or `matplotlib` are missing, install them with:

```bash
python3 -m pip install --user pandas matplotlib
```

### Generated Outputs

The script produces the following outputs in `visualization_output/`:

- `start.png`
- `middle.png`
- `end.png`
- `cyclic_animation.mp4` or `cyclic_animation.gif`

### How the Video Was Produced

The animation was generated directly by the Python visualization script using `matplotlib.animation.FuncAnimation`.

The script first attempts to export the animation as:

- `visualization_output/cyclic_animation.mp4`

If MP4 export is not supported in the environment, it automatically falls back to:

- `visualization_output/cyclic_animation.gif`

Therefore, the animation result was created programmatically from the CSV simulation log, not drawn manually. The video or GIF is the output of the visualization code itself.

If an MP4 file is successfully produced, it can be used directly as the video submission. If only a GIF is generated, that GIF can be kept as the animation result or converted or recorded separately into a video file for presentation.

### Where It Was Run

The simulation itself was built and executed on both:

- the remote environment
- the local machine

The visualization step was run separately after the logs were generated. Since the visualization script requires Python packages such as `pandas` and `matplotlib`, it must be run in an environment where those packages are available.

## Notes

This project was successfully built and executed on the remote environment and on the local machine using explicit Cadmium and Boost include paths during CMake configuration. The configuration files were also corrected to match the expected scenario format of the current implementation.
