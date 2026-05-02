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
- `external/cadmium_v2/`: bundled Cadmium headers
- `external/boost/`: bundled Boost headers
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

## Build Instructions

From the repository root:

```bash
mkdir -p out
cd out
cmake -G Ninja .. -DCADMIUM_V2_DIR=$HOME/assignment/IndoorHumiditySystem-DEVS/external/cadmium/include -DBOOST_DIR=$HOME/smart-fridge-temperature-control-devs/external/boost
cmake --build .
cd ..
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
- visualization images and animation in `visualization_output/`
- video output in the `videos/` folder

## Visualization and Video

The visualization outputs were generated from the simulation log files after running the model. Representative snapshots were saved in `visualization_output/`, and an animated GIF was created to show the temporal evolution of the cyclic cellular automaton.

A video file was then prepared from the visualization output by recording the animation playback and saving it in the `videos/` folder. This provides a video version of the simulation results for submission and presentation.

## Notes

This project was successfully built and executed on the remote environment and on the local machine using explicit Cadmium and Boost include paths during CMake configuration. The configuration files were also corrected to match the expected scenario format of the current implementation.
