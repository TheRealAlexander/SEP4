@echo off

if "%1"=="" goto usage
iot.bat %1 build upload listen test
goto :done

:usage
echo Please specify COM port, example:
echo.
echo    test-avr COM99
goto :done

:done
