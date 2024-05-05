#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

void servo_init(void);           // Initializes the servo hardware (timer, pin, etc.)
void servo_set_angle(uint8_t angle); // Sets the servo to a specific angle

#endif // SERVO_H
