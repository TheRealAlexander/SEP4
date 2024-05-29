static int http_build_request(char *http_buf, int http_cap) {

    // NOTE(rune): Danner først json med separat snprintf, da vi skal bruge længden af json i Content-Length headeren.
    char json_buf[512];
    int json_len = snprintf(
        json_buf, sizeof(json_buf),
        "{"
        "\"temperature\": %d.%d, "
        "\"humidity\": %d.%d, "
        "\"co2\": %d, "
        "\"temperature_ts\": \"%lu\", "
        "\"humidity_ts\": \"%lu\", "
        "\"co2_ts\": \"%lu\""
        "}",
        g_measurements.temperature_integral, g_measurements.temperature_decimal,
        g_measurements.humidity_integral, g_measurements.humidity_decimal,
        g_measurements.co2,
        g_measurements.temperature_timestamp, 
        g_measurements.humidity_timestamp, 
        g_measurements.co2_timestamp
    );

    // Include the JSON string in the HTTP POST request
    int http_len = snprintf(
        http_buf, http_cap,
        "POST /data HTTP/1.0\r\n"
        "Host: indeklima\r\n"
        "Connection: Close\r\n"
        "Accept: application/json\r\n"
        "Accept-Encoding: identity\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "\r\n"
        "%s",
        json_len, json_buf
    );

    return http_len;
}

static int http_trim_inplace(char *http_buf, int http_len) {

    
    int read = 0;
    int write = 0;
    while (read < http_len) {
        if (http_buf[read] == ' ' ||
            http_buf[read] == '\n' ||
            http_buf[read] == '\r' ||
            http_buf[read] == '\t') {

            read++;
        } else {
            http_buf[write] = http_buf[read];
            read++;
            write++;
        }
    }

    http_buf[write] = '\0';
    return write;
}

static bool http_read_bool_from_response(char *response, char *property, bool *value) {
    char needle[128];
    int needle_len = snprintf(needle, sizeof(needle), "\"%s\":", property);
    char *needle_ptr = strstr(response, needle);
    if (needle_ptr) {
        char *value_ptr = needle_ptr + needle_len;
        if (strstr(value_ptr, "true") == value_ptr) {
            *value = true;
            return true;
        }

        if (strstr(value_ptr, "false") == value_ptr) {
            *value = false;
            return true;
        }
    }

    return false;
}

static bool http_read_int_from_response(char *response, char *property, int *value) {
    char needle[128];
    int needle_len = snprintf(needle, sizeof(needle), "\"%s\":", property);
    char *needle_ptr = strstr(response, needle);
    if (needle_ptr) {
        *value = 0;
        char *value_ptr = needle_ptr + needle_len;
        while (*value_ptr >= '0' && *value_ptr <= '9') {
            int digit = *value_ptr - '0';
            *value *= 10;
            *value += digit;

            value_ptr++;
        }
    }

    return false;
}

static void http_process_response(char *http_buf, int http_len) { 
    http_len = http_trim_inplace(http_buf, http_len);
 
    http_read_bool_from_response(http_buf, "openWindow", &g_measurements.open_window);
    http_read_int_from_response(http_buf, "wantNextMeasurementDelay", &g_measurements.want_next_measurement_delay);

    send_to_pc(ANSI_FG_BRIGHT_MAGENTA);
    send_to_pc_fmt("window: %d\n", g_measurements.open_window);
    send_to_pc_fmt("wantNextMeasurementDelay: %d\n", g_measurements.want_next_measurement_delay);
    send_to_pc(ANSI_RESET);
}
