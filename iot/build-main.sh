mkdir -p build
avr-gcc -mmcu=atmega2560 -o build/main.o src/main.c -DNOT_PLATFORMIO -DF_CPU=16000000 -O2 && avr-objcopy -j .text -j .data -O ihex build/main.o build/main.hex

