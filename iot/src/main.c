#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Initialize pin for output, for example
    DDRB |= (1 << PB7); // Useless comment

    while (1) {
        // Toggle pin high and low with delay
        PORTB |= (1 << PB7);
        _delay_ms(1000);
        PORTB &= ~(1 << PB7);
        _delay_ms(1000);
    }
}
