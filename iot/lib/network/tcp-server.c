#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link against the Winsock library

int main() {
    WSADATA wsaData;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char* hello = "Hello from server";

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsaData);

    // Create socket descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return 1;
    }

    // Set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Define the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        perror("Bind failed");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    listen(server_fd, 3);

    // Accept connections
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket == INVALID_SOCKET) {
        perror("Accept failed");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Receive data from client
    recv(new_socket, buffer, sizeof(buffer), 0);
    printf("Message from client: %s\n", buffer);

    // Send data to client
    send(new_socket, hello, strlen(hello), 0);

    // Close sockets
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
