# Cyclic Cellular Automaton Cell-DEVS Model

This repository contains a Cell-DEVS implementation of a cyclic cellular automaton using Cadmium.

## Repository Contents

- `main_cyclic.cpp`: main simulation program
- `include/cyclic_state.hpp`: state definition
- `include/cyclic_grid_cell.hpp`: grid cell transition rules
- `cyclic_config.json`: basic experiment
- `cyclic_config_wrapped.json`: wrapped-boundary experiment
- `cyclic_config_stripes.json`: stripe initialization experiment
- `run_basic.bat`: script for the basic experiment
- `run_wrapped.bat`: script for the wrapped-boundary experiment
- `run_stripes.bat`: script for the stripe initialization experiment
- `logs/`: simulation log files
- `visualization_output/`: generated snapshots and GIF
- `videos/`: simulation video
- `final_report.pdf`: final report
- `DEVSmodelsForm.pdf`: submission form

## External Dependencies

This project requires external libraries/frameworks that are not included in this repository:

- Cadmium v2
- nlohmann/json
- Boost headers
- CMake
- Ninja or Visual Studio Build Tools

## Build

Use a Developer Command Prompt and run:

```bat
mkdir out
cd out
cmake .. -G "Ninja"
cmake --build .
Execution Scripts
run_basic.bat

This script creates the out directory if it does not already exist, builds the project using CMake and Ninja, executes the model using cyclic_config.json for 50 simulation time units, and copies the generated output log to logs/cyclic_basic_log.csv.

run_wrapped.bat

This script creates the out directory if needed, builds the project, executes the model using cyclic_config_wrapped.json for 50 simulation time units, and stores the resulting output log in logs/cyclic_wrapped_log.csv.

run_stripes.bat

This script creates the out directory if needed, builds the project, executes the model using cyclic_config_stripes.json for 50 simulation time units, and stores the resulting output log in logs/cyclic_stripes_log.csv.

Manual Execution

After building, the model can also be executed manually from the out directory.

Basic experiment
main_cyclic.exe ..\cyclic_config.json 50
Wrapped experiment
main_cyclic.exe ..\cyclic_config_wrapped.json 50
Stripes experiment
main_cyclic.exe ..\cyclic_config_stripes.json 50
Output Files

The project produces:

CSV log files in the logs/ folder

visualization images and animation in visualization_output/

video output in the videos/ folder

Notes

This project was developed and tested on Windows using Cadmium v2, CMake, and Ninja.