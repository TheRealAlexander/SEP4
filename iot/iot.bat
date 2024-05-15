@echo off
setlocal

chcp 65001 > nul
cls

if not exist build mkdir build

rem ////////////////////////////////////////////////////////////////
rem // Use toolchain which is checked in to the repo

set path=%path%;%cd%\toolchain\windows\avr8-gnu-toolchain-win32_x86_64\bin
set path=%path%;%cd%\toolchain\windows\avrdude-v7.3-windows-x64

rem ////////////////////////////////////////////////////////////////
rem // Unpack arguments

set port=%1

set build=0
set upload=0
set listen=0
set test=0
set test_local=0

for %%x in (%*) do (
   if "%%~x" == "build"         set build=1
   if "%%~x" == "upload"        set upload=1
   if "%%~x" == "listen"        set listen=1
   if "%%~x" == "test"          set test=1
   if "%%~x" == "test-local"    set test_local=1
)

rem ////////////////////////////////////////////////////////////////
rem // Determine file to compile and determine compiler flags

set avr_flags=-mmcu=atmega2560 -O2 -D F_CPU=16000000 -D BAUD=9600 -Wall -Wextra
set avr_file=src\main.c

if %test% == 1 (
    set avr_file=test\tests.c
    set avr_flags=%avr_flags% -D TESTING=1
)

rem ////////////////////////////////////////////////////////////////
rem // Build

if %build% == 1 (
    avr-gcc %avr_file% %avr_flags% -o build\main.o || goto done
    avr-objcopy -j .text -j .data -O ihex build\main.o build\main.hex || goto done
)

rem ////////////////////////////////////////////////////////////////
rem // Upload to Arduino

if %upload% == 1 (
    avrdude -p atmega2560 -c wiring -P \\.\%port% -b115200 -D -Uflash:w:build\main.hex:i || goto done
    echo Upload succeeded 🤠
)

rem ////////////////////////////////////////////////////////////////
rem // Serial monitor

if %listen% == 1 (
    toolchain\windows\putty\plink.exe -serial %port% -sercfg 9600,8,n,1,N || goto done
)

rem ////////////////////////////////////////////////////////////////
rem // Run test locally

set local_compiler=0
where /q cl  && set local_compiler="cl"
where /q gcc && set local_compiler="gcc"

if %test_local% == 1 (
    if %local_compiler% == "cl"   cl  test\tests.c   /Febuild\tests.exe  /DTESTING=1  /DMOCK=1               && build\tests.exe
    if %local_compiler% == "gcc"  gcc test\tests.c   -o build\tests.exe  -DTESTING=1  -DMOCK=1 -Wall -Wextra && build\tests.exe
    if %local_compiler% == 0      echo No C compiler found. Tried 'gcc' and 'cl'.
)

endlocal

:done