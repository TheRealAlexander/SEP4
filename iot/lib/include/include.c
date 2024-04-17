


#ifdef UNIT_TEST
#include "simple mock avr io.h"
#include "simple mock util delay.h"
#else
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
