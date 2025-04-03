@echo off
REM ============= Windows Batch Script Only =============

REM Create output directory if it doesn't exist
IF NOT EXIST "data\output" (
    mkdir data\output
)

REM Compile the C++ source code
echo Compiling sorting.cpp...
g++ -std=c++17 -O2 src\sorting.cpp -o sort_runner.exe

REM Check for successful compilation
IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful. Running the program...
    sort_runner.exe
) ELSE (
    echo Compilation failed.
)
