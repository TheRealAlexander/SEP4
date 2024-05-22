
clear
set -e
mkdir -p build

# ////////////////////////////////////////////////////////////////
# // Unpack arguments

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

# ////////////////////////////////////////////////////////////////
# // Set configuration variables

if [ -z "$SERVER_IP"     ]; then SERVER_IP="172.20.10.3"; fi
if [ -z "$SERVER_PORT"   ]; then SERVER_PORT=5200; fi
if [ -z "$WIFI_SSID"     ]; then WIFI_SSID="Rune - iPhone"; fi
if [ -z "$WIFI_PASSWORD" ]; then WIFI_PASSWORD=123456789; fi
if [ -z "$HALL_ID"       ]; then HALL_ID=37; fi

# ////////////////////////////////////////////////////////////////
# // Determine file to compile and determine compiler flags

avr_flags="$avr_flags -mmcu=atmega2560"
avr_flags="$avr_flags -O2"
avr_flags="$avr_flags -Wall -Wextra"
avr_flags="$avr_flags -D F_CPU=16000000 -D BAUD=9600"

avr_flags="$avr_flags -D SERVER_IP='\"$SERVER_IP\"'"
avr_flags="$avr_flags -D SERVER_PORT=$SERVER_PORT"
avr_flags="$avr_flags -D WIFI_SSID='\"$WIFI_SSID\"'"
avr_flags="$avr_flags -D WIFI_PASSWORD='\"$WIFI_PASSWORD\"'"
avr_flags="$avr_flags -D HALL_ID=$HALL_ID"

avr_file="src/main.c"
if [ "$test" -eq 1 ]; then
    avr_file="test/tests.c"
    avr_flags="$avr_flags -D TESTING=1"
fi

# ////////////////////////////////////////////////////////////////
# // Build

if [ "$build" -eq 1 ]; then
    eval avr-gcc $avr_file $avr_flags -o build/main.o
    avr-objcopy -j .text -j .data -O ihex build/main.o build/main.hex
fi



# ////////////////////////////////////////////////////////////////
# // Upload to Arduino

if [ "$upload" -eq 1 ]; then
    echo "Upload is not implemented for Linux"
fi

# ////////////////////////////////////////////////////////////////
# // Serial monitor

if [ "$listen" -eq 1 ]; then
    echo "Serial monitor is not implemented for Linux"
fi

# ////////////////////////////////////////////////////////////////
# // Run test locally

if [ "$test_local" -eq 1 ]; then
    cc test/tests.c -o build/tests -DTESTING=1 -DMOCK=1 && build/tests
fi
