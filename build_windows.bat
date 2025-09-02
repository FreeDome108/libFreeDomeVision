@echo off
setlocal enabledelayedexpansion

echo Building anAntaDigital for Windows...

REM Check if CMake is available
where cmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo CMake not found. Please install CMake first.
    echo Download from: https://cmake.org/download/
    exit /b 1
)

REM Check if Visual Studio is available
where cl >nul 2>nul
set VS_AVAILABLE=%ERRORLEVEL%

REM Check if MinGW is available
where g++ >nul 2>nul
set MINGW_AVAILABLE=%ERRORLEVEL%

if %VS_AVAILABLE% neq 0 if %MINGW_AVAILABLE% neq 0 (
    echo Neither Visual Studio nor MinGW found.
    echo Please install Visual Studio or MinGW.
    exit /b 1
)

REM Create build directory
if not exist build_windows mkdir build_windows
cd build_windows

if %VS_AVAILABLE% equ 0 (
    echo Using Visual Studio compiler...
    
    REM Configure with CMake for Visual Studio
    cmake .. ^
        -G "Visual Studio 16 2019" ^
        -A x64 ^
        -DCMAKE_BUILD_TYPE=Release ^
        -DBUILD_SHARED_LIBS=ON ^
        -DBUILD_TESTS=ON ^
        -DBUILD_EXAMPLES=ON ^
        -DENABLE_QUANTUM_FEEDBACK=ON ^
        -DCMAKE_INSTALL_PREFIX=%CD%\install
    
    REM Build
    cmake --build . --config Release --target install
    
) else (
    echo Using MinGW compiler...
    
    REM Configure with CMake for MinGW
    cmake .. ^
        -G "MinGW Makefiles" ^
        -DCMAKE_BUILD_TYPE=Release ^
        -DBUILD_SHARED_LIBS=ON ^
        -DBUILD_TESTS=ON ^
        -DBUILD_EXAMPLES=ON ^
        -DENABLE_QUANTUM_FEEDBACK=ON ^
        -DCMAKE_INSTALL_PREFIX=%CD%\install
    
    REM Build
    cmake --build . --target install
)

if %ERRORLEVEL% equ 0 (
    echo Windows build completed successfully!
    echo Library installed to %CD%\install\lib
    echo Headers installed to %CD%\install\include\anantadigital
    
    REM Show library information
    dir install\lib
) else (
    echo Windows build failed!
    exit /b 1
)

cd ..
