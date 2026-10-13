 @echo off
setlocal
cd /d "%~dp0"

where cmake >nul 2>nul
if errorlevel 1 (
    echo ERRO: CMake nao encontrado no PATH.
    exit /b 1
)

if not exist "CMakeLists.txt" (
    echo ERRO: CMakeLists.txt nao encontrado.
    exit /b 1
)

if not exist "build" mkdir build

cmake -S . -B build -G "MinGW Makefiles"
if errorlevel 1 (
    echo ERRO: configuracao do projeto falhou.
    exit /b 1
)

cmake --build build --parallel
if errorlevel 1 (
    echo ERRO: compilacao falhou.
    exit /b 1
)

echo.
echo Compilacao concluida!
echo Executavel: build\OpenGLProject.exe
exit /b 0