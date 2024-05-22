// tcp-client.h

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>

// Configuration
#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 5200
#define WIFI_SSID   "N/A"
#define WIFI_PASSWORD   "N/A"
#define HALL_ID         37

#define MOCK 1

// Function declarations
int initialize_winsock();
SOCKET create_socket();
int connect_to_server(SOCKET sock, const char* server_ip, int server_port);
int http_build_request(char *http_buf, int http_cap);
int send_and_receive(SOCKET sock, char *request, int request_len, char *response, int response_cap);

// Utility functions (if needed)
void print_request(const char* request);
void print_response(const char* response);

#endif // TCP_CLIENT_H
