\# Cyclic Cellular Automaton Cell-DEVS Model



This repository contains a Cell-DEVS implementation of a cyclic cellular automaton using Cadmium.



\## Repository contents

\- `main\_cyclic.cpp`: main simulation program

\- `include/cyclic\_state.hpp`: state definition

\- `include/cyclic\_grid\_cell.hpp`: grid cell transition rules

\- `cyclic\_config.json`: basic experiment

\- `cyclic\_config\_wrapped.json`: wrapped-boundary experiment

\- `cyclic\_config\_stripes.json`: stripe initialization experiment

\- `logs/`: simulation log files

\- `visualization\_output/`: generated snapshots and GIF

\- `videos/`: simulation video

\- `final\_report.pdf`: final report

\- `DEVSmodelsForm.pdf`: submission form



\## External dependencies

This project requires external libraries/frameworks that are \*\*not included in this repository\*\*:

\- Cadmium v2

\- nlohmann/json

\- Boost headers

\- CMake

\- Ninja or Visual Studio Build Tools



\## Build

Use a Developer Command Prompt and run:



```bat

mkdir out

cd out

cmake .. -G "Ninja"

cmake --build .

