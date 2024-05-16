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