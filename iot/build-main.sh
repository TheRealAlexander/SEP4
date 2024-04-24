mkdir -p build
avr-gcc -mmcu=atmega2560 -o build/main.o src/main.c
avr-objcopy -j .text -j .data -O ihex build/main.o build/main.hex
