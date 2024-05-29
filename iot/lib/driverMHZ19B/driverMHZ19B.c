#define Co2SensorRead 0x86
#define ZERO_POINT_CALIBRATION 0x87
#define SPAN_POINT_CALIBRATION 0x88
#define BAUD_RATE 9600

volatile int latest_co2_concentration = 0;
volatile bool new_co2_data_available = false;

uint8_t rx_buffer[9];
uint8_t rx_count = 0;

void WHZ19B_init(void) {
    uint16_t ubrr_value = (F_CPU / 16 / BAUD_RATE) - 1;
    UBRR3H = (uint8_t)(ubrr_value >> 8);
    UBRR3L = (uint8_t)ubrr_value;
    UCSR3B = (1 << RXEN3) | (1 << TXEN3);
    UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);
}

void reset_rx_buffer() {
    memset(rx_buffer, 0, sizeof(rx_buffer));
    rx_count = 0;
}

void byte_process(uint8_t byte) {
    if (byte == 0xFF && rx_count == 0) {
        rx_buffer[rx_count++] = byte;
    } else if (rx_count > 0) {
        if (rx_count < sizeof(rx_buffer)) {
            rx_buffer[rx_count++] = byte;
            if (rx_count == sizeof(rx_buffer)) {
                uint8_t calculated_checksum = checksum(rx_buffer, sizeof(rx_buffer));
                if (calculated_checksum == rx_buffer[8]) {
                    process_co2_data();
                } 
                reset_rx_buffer();
            }
        } else {
            reset_rx_buffer();
        }
    }
}

void usart3_co2_rx_handler(uint8_t received_byte) {
    byte_process(received_byte);
}

void process_co2_data() {
    uint16_t co2_concentration = calculatePartsPerMil(rx_buffer);
    latest_co2_concentration = co2_concentration;
    new_co2_data_available = true;
}

uint8_t checksum(uint8_t* packet, size_t length) {
    char debug_msg[256] = "Bytes for checksum calculation: ";
    char byte_msg[10];

    for (size_t i = 0; i < length - 1; i++) {
        snprintf(byte_msg, sizeof(byte_msg), "%02X ", packet[i]);
        strcat(debug_msg, byte_msg);
    }
    strcat(debug_msg, "\n");
    //send_to_pc(debug_msg);

    //send_to_pc("Calculating checksum...\n");

    uint8_t calculatedChecksum = checksum2(packet, length);

    snprintf(debug_msg, sizeof(debug_msg), "Expected checksum: %02X, Calculated checksum: %02X\n", packet[length - 1], calculatedChecksum);
    send_to_pc(debug_msg);

    return calculatedChecksum;
}

uint8_t checksum2(uint8_t* packet, size_t length) {
    uint8_t sum = 0;
    for (size_t i = 1; i < length - 1; i++) {
        sum += packet[i];
    }
    return 0xFF - sum + 1;
}

uint16_t calculatePartsPerMil(uint8_t *packet) {
    if (!packet) {
        return 0;
    }

    uint8_t highByte = packet[2];
    uint8_t lowByte = packet[3];

    uint16_t co2_concentration = highByte * 256 + lowByte;

    return co2_concentration;
}

void send_co2_command(uint8_t command_type) {
    uint8_t buf[9] = {0};

    buf[0] = 0xFF;
    buf[1] = 0x01;
    buf[2] = command_type;
    buf[3] = 0x00;
    buf[4] = 0x00;
    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    buf[8] = checksum2(buf, sizeof(buf));

    uart_send_array_blocking(USART_3, buf, sizeof(buf));
}

void sendZeroPointCalibration(void) {
    send_co2_command(ZERO_POINT_CALIBRATION);
}

void sendSpanPointCalibration(uint8_t high_byte, uint8_t low_byte) {
    UNUSED(low_byte);
    UNUSED(high_byte);
    send_co2_command(SPAN_POINT_CALIBRATION);
}

void process_packet(uint8_t *packet) {
    if (!packet) {
        return;
    }

    uint8_t command_type = packet[2];

    switch (command_type) {
        case Co2SensorRead:
            // Process CO2 concentration reading
            {
                uint16_t co2_concentration = calculatePartsPerMil(packet);
                char debug_msg[50];
                snprintf(debug_msg, sizeof(debug_msg), "CO2 Concentration: %u ppm\n", co2_concentration);
                //send_to_pc(debug_msg);
            }
            break;

            // TODO: Add zero span and span point calibrations

        case ZERO_POINT_CALIBRATION:
            // Handle zero point calibration response
            //send_to_pc("Zero point calibration process completed.\n");
            break;

        case SPAN_POINT_CALIBRATION:
            // Handle span point calibration response
            //send_to_pc("Span point calibration process completed.\n");
            break;

        default:
            // Handle unknown packet types
            //send_to_pc("Received packet with unknown command type.\n");
            break;
    }
}
