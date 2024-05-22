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

uint32_t calculate_corrected_time(ntp_response_packet* packet, int32_t subtract_milliseconds) {
    uint32_t t2_seconds = packet->txTm_s;

    // Convert subtract_milliseconds to seconds for correct subtraction from UNIX time
    // Note: subtract_milliseconds / 1000 will handle the conversion to seconds
    // and subtract_milliseconds % 1000 will handle the remaining milliseconds
    int32_t subtract_seconds = subtract_milliseconds / 1000;
    int32_t remaining_milliseconds = subtract_milliseconds % 1000;

    // Convert NTP timestamp to UNIX timestamp
    uint32_t unix_time = t2_seconds - NTP_TIMESTAMP_DELTA - subtract_seconds;

    // Print the relevant data for debugging
    send_to_pc_fmt("t2_seconds: %u (NTP time)\n", t2_seconds);
    send_to_pc_fmt("subtract_milliseconds: %d (milliseconds to subtract)\n", subtract_milliseconds);
    send_to_pc_fmt("UNIX time: %u (after correcting for NTP to UNIX epoch and subtraction)\n", unix_time);

    return unix_time;
}
