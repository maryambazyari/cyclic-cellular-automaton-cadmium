@echo off
setlocal

if "%CADMIUM_V2_DIR%"=="" (
    echo ERROR: CADMIUM_V2_DIR is not set.
    exit /b 1
)

if "%JSON_DIR%"=="" (
    echo ERROR: JSON_DIR is not set.
    exit /b 1
)

if "%BOOST_DIR%"=="" (
    echo ERROR: BOOST_DIR is not set.
    exit /b 1
)

if exist out rmdir /s /q out
mkdir out
cd out

cmake .. -G "Ninja" ^
 -DCADMIUM_V2_DIR="%CADMIUM_V2_DIR%" ^
 -DJSON_DIR="%JSON_DIR%" ^
 -DBOOST_DIR="%BOOST_DIR%"
if errorlevel 1 exit /b 1

cmake --build .
if errorlevel 1 exit /b 1

main_cyclic.exe ..\cyclic_config_stripes.json 50
if errorlevel 1 exit /b 1

if not exist ..\logs mkdir ..\logs
copy /Y cyclic_grid_log.csv ..\logs\cyclic_stripes_log.csv

cd ..
endlocal