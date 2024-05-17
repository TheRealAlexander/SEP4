#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>



#pragma comment(lib, "ws2_32.lib") // Link against the Winsock library

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char *message ="GET / HTTP/1.0\r\n"
    "Host: localhost\r\n"
    "Connection: Close\r\n"
    "\r\n";

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsaData);

    // Create the socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        perror("Socket creation error");
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);
    inet_pton(AF_INET, "216.58.207.238", &serv_addr.sin_addr);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send message
    send(sock, message, strlen(message), 0);
    printf("Message sent\n");

    // Receive server response
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server reply: %s\n", buffer);

    // Close the socket
    closesocket(sock);
    WSACleanup();
    return 0;
}
