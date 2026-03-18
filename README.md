# Cyclic Cellular Automaton Cell-DEVS Model

This repository contains a Cell-DEVS implementation of a cyclic cellular automaton using Cadmium.

## Repository Contents

- `main_cyclic.cpp`: main simulation program
- `include/cyclic_state.hpp`: state definition
- `include/cyclic_grid_cell.hpp`: grid cell transition rules
- `cyclic_config.json`: basic experiment
- `cyclic_config_wrapped.json`: wrapped-boundary experiment
- `cyclic_config_stripes.json`: stripe initialization experiment
- `logs/`: simulation log files
- `visualization_output/`: generated snapshots and GIF
- `videos/`: simulation video
- `final_report.pdf`: final report
- `DEVSmodelsForm.pdf`: submission form

## External Dependencies

This project requires external libraries/frameworks that are **not included in this repository**:

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