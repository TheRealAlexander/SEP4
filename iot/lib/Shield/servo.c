#include "servo.h"
#include <avr/io.h>

// PWM parameters for SG90
#define SERVO_MIN_PULSE_WIDTH 500    // Minimum pulse width in microseconds
#define SERVO_MAX_PULSE_WIDTH 2400   // Maximum pulse width in microseconds
#define SERVO_RANGE 180              // Maximum range of servo from 0 to 180 degrees

void servo_init(void) {
    // Set up Timer 3 for Fast PWM mode on OC3A (PD5/ Digital Pin 5)
    DDRD |= (1 << DDD5); // Set PD5 as an output pin
    TCCR3A = (1 << COM3A1) | (1 << WGM31) | (1 << WGM30); // Fast PWM, non-inverted
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31);   // Prescaler = 8, Fast PWM
    ICR3 = 39999; // Set top value for a 20ms period with 16 MHz clock and prescaler of 8

    // Set the servo to the neutral position initially (90 degrees)
    servo_set_angle(90);
}

void servo_set_angle(uint8_t angle) {
    if (angle > 180) angle = 180; // Limit angle to 0-180 degrees

    // Map the angle to a pulse width
    uint16_t pulse_width = ((SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH) * angle / SERVO_RANGE) + SERVO_MIN_PULSE_WIDTH;

    // Convert pulse width from microseconds to timer ticks
    OCR3A = (pulse_width * 2); // Since the timer frequency is 1 tick = 0.5 µs with prescaler 8 and 16MHz clock
}
