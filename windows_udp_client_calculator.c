//CONNECTIONLESS CLIENT CALCULATOR PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"  
#define SERVER_PORT 12345
#define BUFLEN 512

int main() {
    //Set up Winsock for network communication
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    int slen = sizeof(server);
    char expr[BUFLEN], result[BUFLEN];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    //Create a UDP socket.
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    //Configure server address (IP: 127.0.0.1, Port: 12345).
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    //Prompt user for an arithmetic expression (e.g., "7 * 9").
    printf("Enter expression (e.g., 7 * 9): ");
    
    //Read the expression from standard input and remove trailing newline
    fgets(expr, BUFLEN, stdin);
    expr[strcspn(expr, "\n")] = '\0'; 

    sendto(sock, expr, strlen(expr), 0, (struct sockaddr *)&server, slen);

    //Receive the response from the server.
    memset(result, 0, BUFLEN);
    recvfrom(sock, result, BUFLEN, 0, (struct sockaddr *)&server, &slen);

    //Display the result to the user.
    printf("Result from server: %s\n", result);

    //Close the socket and clean up Winsock resources
    closesocket(sock);
    WSACleanup();
    return 0;
}
