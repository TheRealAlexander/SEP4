#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib") // Link with the Winsock library

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c, read_size;
    char client_message[2000], *header;

    printf("\nInitializing Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    
    printf("Initialized.\n");

    // Create a socket
    if((server_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
        printf("Could not create socket : %d" , WSAGetLastError());
        return 1;
    }

    printf("Socket created.\n");
    
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    // Bind
    if(bind(server_socket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        return 1;
    }
    
    puts("Bind done.");

    // Listen to incoming connections
    listen(server_socket , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    while((client_socket = accept(server_socket , (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
        puts("Connection accepted.");

        // Receive a request from client
        memset(client_message, 0, 2000);
        if((read_size = recv(client_socket, client_message, 2000 , 0)) == SOCKET_ERROR) {
            puts("recv failed");
            continue;
        }

        // Check if it's POST /data HTTP/1.0
        if(strncmp(client_message, "POST /data HTTP/1.0", 18) == 0) {
            // Prepare and send a hardcoded JSON response
            header = "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\n\r\n";
            char* message = "{\"openWindow\": true}\n";
            
            send(client_socket, header, strlen(header), 0);
            send(client_socket, message, strlen(message), 0);
        } else {
            // Send HTTP 404 Not Found
            header = "HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found\n";
            send(client_socket, header, strlen(header), 0);
        }

        closesocket(client_socket);
        puts("Response sent and connection closed.");
    }

    if (client_socket == INVALID_SOCKET) {
        printf("accept failed with error code : %d" , WSAGetLastError());
    }

    // Clean up
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
