#include "ntp.h"

#define LI_NO_LEAP_SECOND 0
#define VN_NTP_VERSION 3
#define MODE_CLIENT 3
#define MODE_SERVER 4
#define STRATUM_MIN 1
#define STRATUM_MAX 15

void construct_ntp_request(ntp_request_packet* packet) {
    memset(packet, 0, sizeof(ntp_request_packet));  // Initialize all fields to 0

    // Set the li, vn, and mode fields.
    packet->li_vn_mode = (LI_NO_LEAP_SECOND << 6) | (VN_NTP_VERSION << 3) | MODE_CLIENT;
}

uint32_t ntohl(uint32_t netlong) {
    return ((netlong>>24)&0xff) | // move byte 3 to byte 0
           ((netlong<<8)&0xff0000) | // move byte 1 to byte 2
           ((netlong>>8)&0xff00) | // move byte 2 to byte 1
           ((netlong<<24)&0xff000000); // byte 0 to byte 3
}

void print_ntp_packet(ntp_packet* packet) {
    send_to_pc_fmt("li_vn_mode: %u\n", packet->li_vn_mode);
    send_to_pc_fmt("stratum: %u\n", packet->stratum);
    send_to_pc_fmt("poll: %u\n", packet->poll);
    send_to_pc_fmt("precision: %u\n", packet->precision);
    send_to_pc_fmt("rootDelay: %u\n", packet->rootDelay);
    send_to_pc_fmt("rootDispersion: %u\n", packet->rootDispersion);
    send_to_pc_fmt("refId: %u\n", packet->refId);
    send_to_pc_fmt("refTm_s: %u\n", packet->refTm_s);
    send_to_pc_fmt("refTm_f: %u\n", packet->refTm_f);
    send_to_pc_fmt("origTm_s: %u\n", packet->origTm_s);
    send_to_pc_fmt("origTm_f: %u\n", packet->origTm_f);
    send_to_pc_fmt("rxTm_s: %u\n", packet->rxTm_s);
    send_to_pc_fmt("rxTm_f: %u\n", packet->rxTm_f);
    send_to_pc_fmt("txTm_s: %u\n", packet->txTm_s);
    send_to_pc_fmt("txTm_f: %u\n", packet->txTm_f);
}

void decode_ntp_response(const uint8_t* buffer, ntp_response_packet* packet) {
    memcpy(packet, buffer, sizeof(ntp_response_packet));

    // Convert all the timestamp fields from Network Byte Order to Host Byte Order
    packet->refTm_s = ntohl(packet->refTm_s);
    packet->refTm_f = ntohl(packet->refTm_f);
    packet->origTm_s = ntohl(packet->origTm_s);
    packet->origTm_f = ntohl(packet->origTm_f);
    packet->rxTm_s = ntohl(packet->rxTm_s);
    packet->rxTm_f = ntohl(packet->rxTm_f);
    packet->txTm_s = ntohl(packet->txTm_s);
    packet->txTm_f = ntohl(packet->txTm_f);

    // Print the decoded packet
    print_ntp_packet(packet);
}

bool is_ntp_response_packet(const uint8_t* buffer, size_t size) {
    if (size != sizeof(ntp_packet)) {
        return false;
    }

    ntp_packet* packet = (ntp_packet*)buffer;

    // Check the version number (VN) field. It should be 3 or 4.
    uint8_t vn = (packet->li_vn_mode >> 3) & 0x07;
    if (vn != VN_NTP_VERSION && vn != VN_NTP_VERSION + 1) {
        return false;
    }

    // Check the mode field. It should be 4, if from a server.
    uint8_t mode = packet->li_vn_mode & 0x07;
    if (mode != MODE_SERVER) {
        return false;
    }

    // Check the stratum field. It should be between 1 and 15 for a valid server.
    if (packet->stratum < STRATUM_MIN || packet->stratum > STRATUM_MAX) {
        return false;
    }

    // Maybe add more checks here... probably not necessary.

    return true;
}

uint32_t calculate_corrected_time(ntp_response_packet* packet, unsigned long long t1, unsigned long long t4) {
    uint32_t t2_seconds = packet->txTm_s;
    uint32_t t2_fraction = packet->txTm_f;
    uint32_t t3_seconds = packet->rxTm_s;
    uint32_t t3_fraction = packet->rxTm_f;

    unsigned long long t2 = ((unsigned long long)t2_seconds << 32) | t2_fraction;
    unsigned long long t3 = ((unsigned long long)t3_seconds << 32) | t3_fraction;

    int64_t delta_t2_t1 = t2 - t1;
    int64_t delta_t3_t4 = t3 - t4;
    int64_t theta = (delta_t2_t1 + delta_t3_t4) / 2;

    uint32_t server_time = t3_seconds;
    server_time += theta;

    // Convert NTP timestamp to UNIX timestamp
    server_time -= NTP_TIMESTAMP_DELTA;

    // Print all variables and values
    send_to_pc_fmt("t1: %lX\n", t1);
    send_to_pc_fmt("t2: %lX\n", t2);
    send_to_pc_fmt("t3: %lX\n", t3);
    send_to_pc_fmt("t4: %lX\n", t4);
    send_to_pc_fmt("delta_t2_t1: %lX\n", delta_t2_t1);
    send_to_pc_fmt("delta_t3_t4: %lX\n", delta_t3_t4);
    send_to_pc_fmt("theta: %lX\n", theta);
    send_to_pc_fmt("server_time: %lX\n", server_time);

    return server_time;
}