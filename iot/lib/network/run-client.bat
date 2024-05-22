@echo off

gcc tcp-client.c -o tcp-client.exe -lws2_32  || goto :done
tcp-client.exe || goto :done

:done
