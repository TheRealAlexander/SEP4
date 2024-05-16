////////////////////////////////////////////////////////////////
// References

// https://github.com/LauritsIvar/sep4_drivers
// https://docs.espressif.com/projects/esp-at/en/latest/esp32/index.html

////////////////////////////////////////////////////////////////
// Macros

#define WIFI2_USART     USART_2
#define WIFI2_BAUDRATE  115200
#define WIFI2_MAX_RECV  2048

////////////////////////////////////////////////////////////////
// Types

typedef enum wifi2_state {
    WIFI2_STATE_NONE,            // Ingen igangv�rende command
                                 
    WIFI2_STATE_DONE_OK,         // Fandt "OK" i respose fra ESP32
    WIFI2_STATE_DONE_FAIL,       // Fandt "ERROR" eller "FAIL" i response fra ESP32

    WIFI2_STATE_WAIT,            // I gang med at l�se normalt AT+XXXXX response.
    WIFI2_STATE_WAIT_IPD,        // I gang med at l�se normalt AT+XXXXX response, og forventer at "+IPD" f�lger.
    WIFI2_STATE_WAIT_IPD_PREFIX, // Venter p� at finde "+IPD,1234:" prefixet.
    WIFI2_STATE_WAIT_IPD_LENGTH, // L�ser tallet efter +"IPD,1234:" prefixet, som fort�ller hvor langt response data er.
    WIFI2_STATE_WAIT_IPD_DATA,   // L�ser data efter "+IPD,1234:" prefixet, indtil vi har modtaget wifi2_g_ipd_len antal bytes.
} wifi2_state;

typedef struct wifi2_cmd_result {
    bool ok;
    char *data;
    int data_len;
} wifi2_cmd_result;

////////////////////////////////////////////////////////////////
// Globals

extern wifi2_state  wifi2_g_state;
extern char         wifi2_g_recv_buf[WIFI2_MAX_RECV];
extern int          wifi2_g_recv_len;

extern int          wifi2_g_ipd_len; // Tallet fra "+IPD,1234:" prefixet gemmes i wifi2_g_ipd_len, og fort�ller hvor langt response data er.
extern int          wifi2_g_ipd_idx; // Index i wifi2_g_recv_buf for data efter "+IPD,1234:" prefixet.

////////////////////////////////////////////////////////////////
// Functions

extern void  wifi2_init();
extern void  wifi2_uart_callback(uint8_t byte);

extern void wifi2_async(char *cmd, bool ipd);
extern void wifi2_async_reset(void);
extern void wifi2_async_ap_join(char *ssid, char *password);
extern void wifi2_async_tcp_open(char *ip, int port);
extern void wifi2_async_tcp_send(char *data, int data_len);
extern void wifi2_async_tcp_close(void);
extern void wifi2_async_udp_open(char *ip, int port);
extern void wifi2_async_udp_send(char *data, int data_len);
extern void wifi2_async_udp_close(void);

extern bool wifi2_can_begin_async(void); // Klar til at starte ny async command?
extern bool wifi2_async_is_done(wifi2_cmd_result *result); // Er seneste async command f�rdig eller har fejlet?

