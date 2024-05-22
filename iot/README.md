# IoT

## Windows

### For at uploade til Arduino:
1. Tilslut Arduino med USB.
2. Åbn command prompt.
3. Skriv `mode` og find hvilken COM port Arduinoen sidder i (f.eks. COM5).
4. `cd` til `iot` mappen.
5. Skriv `upload COM5` (husk at ændr COM5 til den rigtige port) (hvis du bruger powershell, skal du skrive `./upload.bat COM5` i stedet).
6. Serial monitor starter automatisk når upload er færdig. For at stoppe tryk `Ctrl+C` to gange.

WiFi, server ip osv. bliver læst fra enviroment variabler, dvs. for eksempelvis at sætte wifi navn skal du køre `set WIFI_SSID=My wifi name`.
Se `iot\lib\globals.h` for en oversigt over hvilke variabler kan sættes. 

### For at køre unit test:
- Test på Arduino: Kør `test-avr COM5` fra `iot` mappen (trin 1-4 ligesom ovenfor).
- Test på egen PC: Kør `test-local` fra `iot` mappen.

### For at køre integration test

Integration test kan enten kører med *fake arduino og real backend* eller *real arduino og fake backend*.

Fake arduino og real backend:
- Start backend med `docker compose up`
- Vent på at alle microservices er færdig med startup
- `cd` til `iot\lib\network` og kør `run-client.bat`

Real arduino og fake backend:
- Sæt enviroment variabler. Eksempel:
```
set WIFI_SSID=Fatema - iPhone
set WIFI_PASSWORD=12345678
set SERVER_IP=172.20.10.5
set SERVER_PORT=8080
```
- [Upload til Arduino](###for-at-uploade-til-arduino)
- `cd` til `iot\lib\network` og kør `run-server.bat`

### Forklaring

Alle dependencies (inklusiv compiler, linker, osv.) til AVR udvikling på Windows, er tjekket ind i repositoriet. 
Du kan manuelt finde dem i `iot\toolchain`, eller du kan bruge `iot.bat` sciptet.

`iot.bat` scriptet kan kaldes med følgende argumenter:
- `build` bygger AVR hex fil.
- `upload` flasher AVR hex fil til Arduino.
- `listen` starter serial monitor.
- `test` bygger `tests.c` i stedet for `main.c`.
- `test-local` bygger og kører test på egen PC.

COM port til upload og/eller serial monitor skal altid være første argument.
Eksempel: For at bygge, uploade og starte serial monitor, kør `iot COM99 build upload listen`.

For at spare på tastaturet kan du bruge følgende scripts. De kalder bare `iot.bat` med forskellige argumenter.
- `upload COM5` kører `main.c` på Arduino.
- `test-avr COM5` kører `tests.c` på Arduino.
- `test-local` kører testene på egen PC.

## Linux

Ligesom `iot.bat` er der en `iot.sh` til Linux. Ikke alle funktioner er implementeret her, men der er nok til at GitHub workflowet kan bygge en AVR hex fil, og køre testene lokalt.

## VS Code/Platform IO

Åbn `iot` mappen med VS Code.
Skift til enviroment `env:atmega2560`, og tryk upload + serial monitor, for at køre `src\main.c` på Arduino.
Skift til enviroment `env:atmega2560_test`, og tryk upload + serial monitor, for at køre `test\tests.c` på Arduino.
