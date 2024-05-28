////////////////////////////////////////////////////////////////
// Global timekeeping

typedef uint64_t timestamp;

static timestamp g_timestamp;

////////////////////////////////////////////////////////////////
// Global measurements

typedef struct measurements {
    // From sensors
    uint8_t humidity_integral;     
    uint8_t humidity_decimal;      
    uint8_t temperature_integral;  
    uint8_t temperature_decimal;   
    uint16_t co2;

    // Timestamp from sensors
    timestamp humidity_timestamp;
    timestamp temperature_timestamp;
    timestamp co2_timestamp;

    // From backend
    bool open_window;
    int want_next_measurement_delay;
} measurements;

static measurements g_measurements;
