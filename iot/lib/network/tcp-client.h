// tcp-client.h

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>

#define MOCK 1

// Function declarations
int initialize_winsock();
SOCKET create_socket();
int connect_to_server(SOCKET sock, const char* server_ip, int server_port);
int send_and_receive(SOCKET sock, char *request, int request_len, char *response, int response_cap);

// Utility functions (if needed)
void print_request(const char* request);
void print_response(const char* response);

#endif // TCP_CLIENT_H
