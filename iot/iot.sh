
clear
set -e
mkdir -p build

# Create config based on config_default.h
if [ ! -e "lib/config.h" ]; then cp lib/config_default.h lib/config.h; fi

# --------------------------------------------
# Unpack arguments

build=0
upload=0
listen=0
test=0
test_local=0

for arg in "$@"; do
    [ "$arg" == "build" ]      && build=1
    [ "$arg" == "upload" ]     && upload=1
    [ "$arg" == "listen" ]     && listen=1
    [ "$arg" == "test" ]       && test=1
    [ "$arg" == "test-local" ] && test_local=1
done

# --------------------------------------------
# AVR build, upload and test

avr_flags="-mmcu=atmega2560 -O2 -Wall -Wextra -D F_CPU=16000000 -D BAUD=9600"
avr_file="src/main.c"
if [ "$test" -eq 1 ]; then
    avr_file="test/tests.c"
    avr_flags="$avr_flags -D TESTING=1"
fi

if [ "$build" -eq 1 ]; then
    eval avr-gcc $avr_file $avr_flags -o build/main.o
    avr-objcopy -j .text -j .data -O ihex build/main.o build/main.hex
fi

if [ "$upload" -eq 1 ]; then
    echo "Upload is not implemented for Linux"
fi

if [ "$listen" -eq 1 ]; then
    echo "Serial monitor is not implemented for Linux"
fi

# --------------------------------------------
# Local build and test

if [ "$test_local" -eq 1 ]; then
    cc test/tests.c -o build/tests -DTESTING=1 -DMOCK=1 && build/tests
fi
