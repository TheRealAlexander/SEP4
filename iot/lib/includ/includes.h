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

// TEMPORARY HACK 
// TEMPORARY HACK 
// TEMPORARY HACK
#if MOCK

// NOTE(rune): På Windows har C standard library ikke memmem(), s+ jeg har hugget en implementation her fra: https://stackoverflow.com/a/52989329
// TODO(rune): Vi bruger kun memmem() i wifi2.c, men vi kan godt undvære det kode, som tjekker efter "OK", "ERROR" osv.
void *memmem(void *haystack, size_t haystack_len,
             void * needle, size_t needle_len) {
    if (haystack == NULL) return NULL; // or assert(haystack != NULL);
    if (haystack_len == 0) return NULL;
    if (needle == NULL) return NULL; // or assert(needle != NULL);
    if (needle_len == 0) return NULL;

    for (char *h = haystack;
         haystack_len >= needle_len;
         ++h, --haystack_len) {
        if (!memcmp(h, needle, needle_len)) {
            return h;
        }
    }
    return NULL;
}

#endif

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
// Include drivers

#include "uart/uart.h"
#include "uart/uart.c"
#include "print/print.h"
#include "print/print.c"
#include "driverMHZ19B/driverMHZ19B.h"
#include "driverMHZ19B/driverMHZ19B.c"
#include "Periodic/periodic_task.h"
#include "Periodic/periodic_task.c"
#include "dht11/dht11.h"
#include "dht11/dht11.c"
#include "wifi/wifi2.h"
#include "wifi/wifi2.c"
#include "servo/servo.h"
#include "servo/servo.c"
#include "tone/tone.h"
#include "tone/tone.c"
#include "buttons/buttons.h"
#include "buttons/buttons.c"
#include "display/display.h"
#include "display/display.c"
#include "display_button/display_button.h"
#include "display_button/display_button.c"
#include "network/tcp-client.c"
#include "network/tcp-server.c"

////////////////////////////////////////////////////////////////
// Include testing framework

#if TESTING
#include "testing/testing.h"
#include "testing/testing.c"
#endif
