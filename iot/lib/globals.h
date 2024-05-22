////////////////////////////////////////////////////////////////
// Global settings

#ifndef SERVER_IP
#error "SERVER_IP not defined"
#endif

#ifndef SERVER_PORT
#error "SERVER_PORT not defined"
#endif

#ifndef WIFI_SSID
#error "WIFI_SSID not defined"
#endif

#ifndef WIFI_PASSWORD
#error "WIFI_PASSWORD not defined"
#endif

#ifndef HALL_ID
#error "HALL_ID not defined"
#endif

////////////////////////////////////////////////////////////////
// Global measurements

typedef struct measurements {
    // NOTE(rune): From sensors
    uint8_t humidity_integral;    // Før komma
    uint8_t humidity_decimal;     // Efter komma
    uint8_t temperature_integral; // Før komma
    uint8_t temperature_decimal;  // Efter komma
    uint16_t co2;

    // NOTE(rune): From backend
    bool open_window;
    int want_next_measurement_delay;
} measurements;

static measurements g_measurements;

////////////////////////////////////////////////////////////////
// Global timekeeping

typedef uint64_t timestamp;

static timestamp g_timestamp;
