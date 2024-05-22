// tcp-client.c

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "tcp-client.h"
#include "../includes.h"


#pragma comment(lib, "ws2_32.lib") // Link against the Winsock library

// Initialize Winsock
int initialize_winsock() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2,2), &wsaData);
}

// Create the socket
SOCKET create_socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

// Connect to the server
int connect_to_server(SOCKET sock, const char* server_ip, int server_port) {
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);

    return connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
}

// Send and receive data
int send_and_receive(SOCKET sock, char *request, int request_len, char *response, int response_cap) {
    send(sock, request, request_len, 0);

    int response_len = 0;
    while (1) {
        int recv_len = recv(sock, response + response_len, response_cap - response_len, 0);
        if (recv_len <= 0 || response_len + recv_len > response_cap) {
            break; // Connection closed or error
        }
        response_len += recv_len;
    }

    response[response_len] = '\0'; // Null-terminate the response
    return response_len;
}

// Utility functions for printing
void print_request(const char* request) {
    send_to_pc_fmt(ANSI_FG_BRIGHT_MAGENTA);
    send_to_pc_fmt("REQUEST\n");
    send_to_pc_fmt(ANSI_FG_MAGENTA);
    send_to_pc_fmt("%s\n", request);
    send_to_pc_fmt(ANSI_RESET);
}

void print_response(const char* response) {
    send_to_pc_fmt(ANSI_FG_BRIGHT_CYAN);
    send_to_pc_fmt("RESPONSE\n");
    send_to_pc_fmt(ANSI_FG_CYAN);
    send_to_pc_fmt("%s\n", response);
    send_to_pc_fmt(ANSI_RESET);
}

int main() {
    // Initialize Winsock
    if (initialize_winsock() != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    // Create the socket
    SOCKET sock = create_socket();
    if (sock == INVALID_SOCKET) {
        perror("Socket creation error");
        WSACleanup();
        return 1;
    }

    // Connect to the server
    if (connect_to_server(sock, SERVER_IP, SERVER_PORT) < 0) {
        perror("Connection Failed");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Build and send the request
    char request[2048] = {0};
    int request_len = http_build_request(request, sizeof(request));
    print_request(request);

    // Receive the response
    char response[2048] = {0};
    int response_len = send_and_receive(sock, request, request_len, response, sizeof(response));
    print_response(response);

    // Close the socket
    closesocket(sock);
    WSACleanup();
    return 0;
}
