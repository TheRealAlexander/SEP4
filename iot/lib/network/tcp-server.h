// tcp-server.h

#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <stdbool.h>
#include <winsock2.h>

// Configuration
#define SERVER_IP       "N/A"
#define SERVER_PORT     8080
#define WIFI_SSID       "N/A"
#define WIFI_PASSWORD   "N/A"
#define HALL_ID         -1
#define MOCK 1

// Function declarations
int initialize_winsock();
SOCKET create_server_socket();
int set_socket_options(SOCKET server_socket);
int bind_server_socket(SOCKET server_socket, struct sockaddr_in* address);
void handle_client(SOCKET client_socket);
void send_response(SOCKET client_socket, bool open_window);
void print_request(const char* request);
void print_response(const char* response);

#endif // TCP_SERVER_H
