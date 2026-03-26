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
- `visualization_output/`: generated snapshots and GIF
- `videos/`: simulation video
- `external/nlohmann/json.hpp`: bundled JSON single-header dependency
- `cyclic_cellular_automaton_report.pdf`: final report

## External Dependencies

This project requires the following external tools and libraries:

- Cadmium
- Boost headers
- CMake 3.16 or newer
- Ninja or another supported build generator
- A C++17 compiler

The repository already includes `nlohmann/json` as a local header dependency in `external/nlohmann/json.hpp`.

## Build on Linux

Run the following commands from the repository root:

```bash
mkdir -p out
cd out
cmake -G Ninja \
  -DCADMIUM_V2_DIR=/path/to/cadmium/include \
  -DBOOST_DIR=/path/to/boost \
  ..
cmake --build .
```

### Example build command on the remote environment

```bash
mkdir -p out
cd out
cmake -G Ninja \
  -DCADMIUM_V2_DIR=/home/Bazyari/cadmium/include \
  -DBOOST_DIR=/home/Bazyari/boost_full \
  ..
cmake --build .
```

## Build on Windows

Use a Developer Command Prompt and run:

```bat
mkdir out
cd out
cmake .. -G "Ninja" ^
  -DCADMIUM_V2_DIR="path\to\cadmium\include" ^
  -DBOOST_DIR="path\to\boost"
cmake --build .
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

## Manual Execution

After building, the model can also be executed manually from the `out` directory.

### Linux

```bash
./main_cyclic ../cyclic_config.json 50
./main_cyclic ../cyclic_config_wrapped.json 50
./main_cyclic ../cyclic_config_stripes.json 50
```

### Windows

```bat
main_cyclic.exe ..\cyclic_config.json 50
main_cyclic.exe ..\cyclic_config_wrapped.json 50
main_cyclic.exe ..\cyclic_config_stripes.json 50
```

## Output Files

The project produces:

- CSV log files in the `logs/` folder
- visualization images and animation in `visualization_output/`
- video output in the `videos/` folder

## Notes

This project was updated to build and run successfully in the remote environment using Cadmium and Boost paths supplied at CMake configuration time.
