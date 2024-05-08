@echo off
setlocal

chcp 65001 > nul

if "%1"=="" goto usage

set port=%1

set path=%path%;%cd%\toolchain\windows\avr8-gnu-toolchain-win32_x86_64\bin
set path=%path%;%cd%\toolchain\windows\avrdude-v7.3-windows-x64

cls
if not exist build mkdir build
if %errorlevel% == 0 avr-gcc -mmcu=atmega2560 src\main.c -o build\main.o -O2 -D F_CPU=16000000 -D BAUD=9600 -D NOT_PLATFORMIO -Wno-implicit-int -Wno-misspelled-isr
if %errorlevel% == 0 avr-objcopy -j .text -j .data -O ihex build\main.o build\main.hex
if %errorlevel% == 0 avrdude -p atmega2560 -c wiring -P \\.\%port% -b115200 -D -Uflash:w:build\main.hex:i
if %errorlevel% == 0 echo Upload succeeded 🤠
if %errorlevel% == 0 listen %port%
goto :done

:usage
echo Please specify COM port and file name, example:
echo.
echo    upload COM3
goto :done

:done
endlocal