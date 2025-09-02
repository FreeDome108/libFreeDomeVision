@echo off
echo Building anAntaDigital for Windows...

REM Create build directory
if not exist build_windows mkdir build_windows
cd build_windows

REM Configure with CMake
cmake .. ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DBUILD_SHARED_LIBS=ON ^
    -DBUILD_TESTS=ON ^
    -DBUILD_EXAMPLES=ON ^
    -DENABLE_QUANTUM_FEEDBACK=ON

REM Build
cmake --build . --config Release --parallel

REM Run tests
if %ERRORLEVEL% EQU 0 (
    echo Build successful! Running tests...
    ctest --output-on-failure
) else (
    echo Build failed!
    exit /b 1
)

echo Windows build completed!
pause
