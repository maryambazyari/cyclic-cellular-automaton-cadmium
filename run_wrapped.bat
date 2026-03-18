@echo off
if not exist out mkdir out
cd out
cmake .. -G "Ninja"
cmake --build .
main_cyclic.exe ..\cyclic_config_wrapped.json 50
if not exist ..\logs mkdir ..\logs
copy /Y cyclic_grid_log.csv ..\logs\cyclic_wrapped_log.csv
cd ..