@echo off

gcc tcp-server.c -o tcp-server.exe -lws2_32  || goto :done
tcp-server.exe || goto :done

:done
