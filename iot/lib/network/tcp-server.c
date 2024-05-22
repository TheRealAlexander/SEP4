// tcp-server.c er en fake backend, som forbinder til en rigtig arduino.

////////////////////////////////////////////////////////////////
// Include standard library and OS headers

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link against the Winsock library

////////////////////////////////////////////////////////////////
// Fake configuration

#define SERVER_IP       "N/A"
#define SERVER_PORT     0
#define WIFI_SSID       "N/A"
#define WIFI_PASSWORD   "N/A"
#define HALL_ID         -1
#define MOCK 1

////////////////////////////////////////////////////////////////
// Include dependencies

#include "../includes.h"

////////////////////////////////////////////////////////////////
// Main

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create socket descriptor
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return 1;
    }

    // Set socket options
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Define the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        perror("Bind failed");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    listen(server_socket, 3);

    // Accept connections
    bool open_window = false;
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&address, &addrlen);
        if (client_socket == INVALID_SOCKET) {
            perror("Accept failed");
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        // Receive request from client
        char request[2048] = { 0 };
        int request_len = recv(client_socket, request, sizeof(request), 0);
        request[request_len] = '\0';

        // Print request
        send_to_pc_fmt(ANSI_FG_BRIGHT_MAGENTA);
        send_to_pc_fmt("REQUEST\n");
        send_to_pc_fmt(ANSI_FG_MAGENTA);
        send_to_pc_fmt("%s\n", request);
        send_to_pc_fmt(ANSI_RESET);

        // Send response
        char response[2024] = { 0 };
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

        // Print response
        send_to_pc_fmt(ANSI_FG_BRIGHT_CYAN);
        send_to_pc_fmt("RESPONSE\n");
        send_to_pc_fmt(ANSI_FG_CYAN);
        send_to_pc_fmt("%s\n", response);
        send_to_pc_fmt(ANSI_RESET);

        // Close socket
        closesocket(client_socket);

        open_window = !open_window;
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
