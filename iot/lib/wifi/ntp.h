#pragma once

#include <stdint.h>
#include <stdbool.h>

#define NTP_TIMESTAMP_DELTA 2208988800ull

typedef struct {
    uint8_t li_vn_mode;       // Eight bits. li, vn, and mode.
    uint8_t stratum;          // Eight bits. Stratum level of the local clock.
    uint8_t poll;             // Eight bits. Maximum interval between successive messages.
    uint8_t precision;        // Eight bits. Precision of the local clock.

    uint32_t rootDelay;       // 32 bits. Total round trip delay time.
    uint32_t rootDispersion;  // 32 bits. Max error aloud from primary clock source.
    uint32_t refId;           // 32 bits. Reference clock identifier.

    uint32_t refTm_s;         // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f;         // 32 bits. Reference time-stamp fraction of a second.

    uint32_t origTm_s;        // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f;        // 32 bits. Originate time-stamp fraction of a second.

    uint32_t rxTm_s;          // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f;          // 32 bits. Received time-stamp fraction of a second.

    uint32_t txTm_s;          // 32 bits. Transmit time-stamp seconds.
    uint32_t txTm_f;          // 32 bits. Transmit time-stamp fraction of a second.

} ntp_packet;                 // Total: 384 bits or 48 bytes.

typedef ntp_packet ntp_request_packet;
typedef ntp_packet ntp_response_packet;

void construct_ntp_request(ntp_request_packet* packet);
void decode_ntp_response(const uint8_t* buffer, ntp_response_packet* packet);
bool is_ntp_packet_valid(const uint8_t* buffer, size_t size);
uint32_t calculate_corrected_time(ntp_response_packet* packet, uint32_t t1, uint32_t t4);