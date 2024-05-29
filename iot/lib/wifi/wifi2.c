////////////////////////////////////////////////////////////////
// Functions

static void wifi2_init() {
    uart_init(WIFI2_USART, WIFI2_BAUDRATE, wifi2_uart_callback);
}

static bool wifi2_can_begin_async(void) {
    return wifi2_g_state == WIFI2_STATE_NONE;
}

static bool wifi2_async_is_done(wifi2_cmd_result *result) {
    result->ok = false;

    switch (wifi2_g_state) {
        case WIFI2_STATE_DONE_OK: {
            wifi2_g_state = WIFI2_STATE_NONE; // NOTE(rune): Marker at vi er klar til næste command
            result->ok = true;
            return true;
        }

        case WIFI2_STATE_DONE_FAIL: {
            wifi2_g_state = WIFI2_STATE_NONE; // NOTE(rune): Marker at vi er klar til næste command
            return true;
        }

        default: {
            return false;
        }
    }
}

static void wifi2_cancel_async(void) {
    wifi2_g_state = WIFI2_STATE_NONE;
}

static void wifi2_async(char *cmd) {
    memset(wifi2_g_recv_buf, 0, sizeof(wifi2_g_recv_buf));
    wifi2_g_recv_len = 0;
    wifi2_g_state = WIFI2_STATE_WAIT;

    uart_send_string_blocking(WIFI2_USART, cmd);
}

static void wifi2_uart_callback(uint8_t byte) {
    if (wifi2_g_recv_len < isizeof(wifi2_g_recv_buf)) {
        wifi2_g_recv_buf[wifi2_g_recv_len++] = byte;
    }

    if (wifi2_g_state == WIFI2_STATE_WAIT) {
        static char *look_for[] = {
            "OK", "FAIL", "ERROR"
        };

        for (int i = 0; i < countof(look_for); i++) {
            int look_for_len = strlen(look_for[i]);
            if (look_for_len <= wifi2_g_recv_len) {
                char *check = wifi2_g_recv_buf + wifi2_g_recv_len - look_for_len;
                if (memcmp(check, look_for[i], look_for_len) == 0) {
                    if (i == 0) {
                        wifi2_g_state = WIFI2_STATE_DONE_OK;
                    } else {
                        wifi2_g_state = WIFI2_STATE_DONE_FAIL;
                    }
                    break;
                }
            }
        }
    }
}

static void wifi2_async_reset(void) {
    char *cmd = "AT+RST\r\n";
    wifi2_async(cmd);
}

static void wifi2_async_ap_join(char *ssid, char *password) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    wifi2_async(cmd);
}

static void wifi2_async_tcp_open(char *ip, int port) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ip, port);
    wifi2_async(cmd);
}

static void wifi2_async_tcp_send(char *data, int data_len) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d\r\n", data_len);
    wifi2_async(cmd);
    _delay_ms(20);
    uart_send_array_blocking(WIFI2_USART, (uint8_t *)data, data_len);
}

static void wifi2_async_tcp_close(void) {
    char *cmd = "AT+CIPCLOSE\r\n";
    wifi2_async(cmd);
}

static void wifi2_async_udp_open(char *ip, int port) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"UDP\",\"%s\",%d\r\n", ip, port);
    wifi2_async(cmd);
}

static void wifi2_async_udp_send(char *data, int data_len) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d\r\n", data_len);
    wifi2_async(cmd);
    _delay_ms(20);
    uart_send_array_blocking(WIFI2_USART, data, data_len);
}

static void wifi2_async_udp_close(void) {
    // Same as tcp close
    wifi2_async_tcp_close();
}
