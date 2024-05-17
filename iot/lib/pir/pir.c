#define PIR_DDR  DDRD
#define PIR_BIT  (1 << PD2)
#define PIR_PORT PORTD
#define PIR_PIN  PIND

static void pir_init(void) {
    PIR_DDR  &= ~PIR_BIT;
    PIR_PORT |=  PIR_BIT;
}

static bool pir_motion(void) {
    bool motion = (PIR_PIN & PIR_BIT) != 0;
    return motion;
}