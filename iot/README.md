# IOT 

## Windows toolchain
For at uploade til arduino:
1. Tilslut Arduino med USB
2. Åbn command prompt
3. Skriv `mode` og find hvilken COM port Arduinoen sidder i (f.eks. `COM5`)
4. `cd` til `/iot`
5. Skriv `upload COM5` (husk at ændr COM5 til den rigtige port) (hvis du bruger powershell, skal du skrive `./upload.bat COM5`)
6. Serial monitor starter automatisk når upload efter færdig, for at stoppe trykke `Ctrl+C` to gange. 

`upload.bat` compiler koden i `main.c`. Alting bliver compilet i en translation unit.

