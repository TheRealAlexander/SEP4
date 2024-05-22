#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define MOCK 1
#include "../includes.h"

#pragma comment(lib, "ws2_32.lib") // Link against the Winsock library

static int build_http_request(char *http_buf, int http_cap) {

    // Fake measurements
    int temperature_integral = 1;
    int temperature_decimal = 2;
    int humidity_integral = 3;
    int humidity_decimal = 4;
    int co2 = 5;
    int hall_id = 6;

    // Json
    char json_buf[256];
    int json_len = snprintf(
        json_buf, sizeof(json_buf),
        "{"
        "\"temperature\": %d.%d, "
        "\"humidity\": %d.%d, "
        "\"co2\": %d, "
        "\"hallId\": %d"
        "}",
        temperature_integral, temperature_decimal,
        humidity_integral, humidity_decimal,
        co2,
        hall_id
    );

    // Http
    int http_len = snprintf(
        http_buf, http_cap,
        "POST /PostEnvironmentData HTTP/1.0\r\n"
        "Host: tcp-client\r\n"
        "Connection: Close\r\n"
        "Accept: application/json\r\n"
        "Accept-Encoding: identity\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "\r\n"
        "%s",
        json_len, json_buf
    );

    return http_len;
}


int main() {
    // Server
    char *server_ip   = "127.0.0.1"; // localhost
    int   server_port = 5200; // indeklima microservice

    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    // Create the socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        perror("Socket creation error");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send request
    char request[2048]  = { 0 };
    int  request_len = build_http_request(request, sizeof(request));
    send(sock, request, request_len, 0);

    // Print request
    send_to_pc_fmt(ANSI_FG_BRIGHT_MAGENTA);
    send_to_pc_fmt("REQUEST\n");
    send_to_pc_fmt(ANSI_FG_MAGENTA);
    send_to_pc_fmt("%s\n", request);
    send_to_pc_fmt(ANSI_RESET);

    // Receive server response
    char response[2048] = { 0 };
    int  response_len = 0;
    while (1) {
        int recv_len = recv(sock, response + response_len, sizeof(response) - response_len, 0);

        if (response_len + recv_len > sizeof(response)) {
            break; // Not enough space in the recieve buffer.
        }
        
        if (recv_len == 0) {
            break; // Connection has closed gracefully.
        }

        response_len += recv_len;
    }

    // Print response
    send_to_pc_fmt(ANSI_FG_BRIGHT_CYAN);
    send_to_pc_fmt("RESPONSE\n");
    send_to_pc_fmt(ANSI_FG_CYAN);
    send_to_pc_fmt("%s\n", response);
    send_to_pc_fmt(ANSI_RESET);


    // Close the socket
    closesocket(sock);
    WSACleanup();
    return 0;
}
