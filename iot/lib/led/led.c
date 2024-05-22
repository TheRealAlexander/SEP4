////////////////////////////////////////////////////////////////
// Built-in LEDs on shield

static void led_init(void) {
    DDRB = 0xff;
}

static void led_set(uint8_t bits) {
    PORTB = bits;
}

static void led_blink(int how_many_times) {
    while (how_many_times--) {
        led_set(0xff);
        _delay_ms(100);
        led_set(0x00);
        _delay_ms(100);
    }
}
