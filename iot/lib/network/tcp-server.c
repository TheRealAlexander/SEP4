// tcp-server.c

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "tcp-server.h"
#include "../includes.h"


#pragma comment(lib, "ws2_32.lib")  // Link against the Winsock library

// Initialize Winsock
int initialize_winsock() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

// Create the server socket
SOCKET create_server_socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

// Set socket options
int set_socket_options(SOCKET server_socket) {
    int opt = 1;
    return setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
}

// Bind the server socket
int bind_server_socket(SOCKET server_socket, struct sockaddr_in* address) {
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(SERVER_PORT);

    return bind(server_socket, (struct sockaddr*)address, sizeof(*address));
}

// Handle client connection
void handle_client(SOCKET client_socket) {
    char request[2048] = { 0 };
    int request_len = recv(client_socket, request, sizeof(request), 0);
    request[request_len] = '\0';

    print_request(request);

    static bool open_window = false;
    send_response(client_socket, open_window);
    open_window = !open_window;
}

// Send response to client
void send_response(SOCKET client_socket, bool open_window) {
    char response[2048] = { 0 };
    int response_len = snprintf(
        response,
        sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 56\r\n"
        "Connection: close\r\n"
        "Content-Type: application/json\r\n"
        "Date: Wed, 22 May 2024 08:58:59 GMT\r\n"
        "Server: Kestrel\r\n"
        "\r\n"
        "{\"success\":true,\"code\":0,\"hallId\":37,\"openWindow\":%s}",
        open_window ? "true" : "false"
    );

    send(client_socket, response, response_len, 0);
    print_response(response);
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
    if (initialize_winsock() != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    SOCKET server_socket = create_server_socket();
    if (server_socket == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return 1;
    }

    if (set_socket_options(server_socket) == SOCKET_ERROR) {
        perror("Set socket options failed");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    struct sockaddr_in address;
    if (bind_server_socket(server_socket, &address) == SOCKET_ERROR) {
        perror("Bind failed");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, 3) == SOCKET_ERROR) {
        perror("Listen failed");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    int addrlen = sizeof(address);
    while (1) {
        SOCKET client_socket = accept(server_socket, (struct sockaddr*)&address, &addrlen);
        if (client_socket == INVALID_SOCKET) {
            perror("Accept failed");
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        handle_client(client_socket);
        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
