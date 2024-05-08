@echo off
setlocal

if "%1"=="" goto usage
set port=%1
toolchain\windows\putty\plink.exe -serial %port% -sercfg 9600,8,n,1,N
goto :done

:usage
echo Please specify COM port, example:
echo.
echo    listen COM3
goto :done

:done
endlocal