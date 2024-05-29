////////////////////////////////////////////////////////////////
// Macros

#define countof(a)          ((int)(sizeof(a) / sizeof(*(a))))
#define isizeof(a)          ((int)(sizeof(a)))
#define UNUSED(a)           ((void)(a)) // NOTE(rune): To supress unused variable warnings

////////////////////////////////////////////////////////////////
// Include standard library

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////
// Include AVR or mock AVR

#if MOCK
#   include "mock_avr.h"
#else
#   include <util/delay.h>
#   include <avr/io.h>
#   include <avr/interrupt.h>
#endif

////////////////////////////////////////////////////////////////
// Include globals 

#include "globals.h"

////////////////////////////////////////////////////////////////
// Include user config

#include "config.h"

////////////////////////////////////////////////////////////////
// Include drivers

#include "uart/uart.h"
#include "uart/uart.c"
#include "print/print.h"
#include "print/print.c"
#include "http/http.h"
#include "http/http.c"
#include "driverMHZ19B/driverMHZ19B.h"
#include "driverMHZ19B/driverMHZ19B.c"
#include "Periodic/periodic_task.h"
#include "Periodic/periodic_task.c"
#include "dht11/dht11.h"
#include "dht11/dht11.c"
#include "wifi/wifi2.h"
#include "wifi/wifi2.c"
#include "wifi/ntp.h"
#include "wifi/ntp.c"
#include "servo/servo.h"
#include "servo/servo.c"
#include "tone/tone.h"
#include "tone/tone.c"
#include "led/led.h"
#include "led/led.c"
#include "buttons/buttons.h"
#include "buttons/buttons.c"
#include "display/display.h"
#include "display/display.c"
#include "display_button/display_button.h"
#include "display_button/display_button.c"
#include "pir/pir.h"
#include "pir/pir.c"

////////////////////////////////////////////////////////////////
// Include testing framework

#if TESTING
#include "testing/testing.h"
#include "testing/testing.c"
#endif

