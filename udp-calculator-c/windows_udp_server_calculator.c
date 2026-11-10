//CONNECTIONLESS SERVER CALCULATOR PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 12345
#define BUFLEN 512

int main() {
    //set up Winsock 
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server, client;
    int slen = sizeof(client);
    char buf[BUFLEN], result[BUFLEN];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    //create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    //configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    //bind socket to server address
    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("UDP server is running on port %d...\n", PORT);

    //listen for incoming UDP datagrams from clients
    while (1) {
        memset(buf, 0, BUFLEN);
        //receive an expression
        recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *)&client, &slen);

        printf("Received: %s\n", buf);

        int num1, num2;
        char op;
        int consumed = sscanf(buf, "%d %c %d", &num1, &op, &num2);
        //If parsing fails (fewer than 3 components), prepare error message: "Invalid format".
        if (consumed != 3) {
            snprintf(result, BUFLEN, "Error: Invalid format");
        } else if (op == '/' && num2 == 0) {
           //If operator is division (/) and num2 is 0, prepare error message: "Division by zero".
            snprintf(result, BUFLEN, "%d / 0 = Error: Division by zero", num1);
        } else {
            //If valid, perform the arithmetic operation based on the operator
            int res;
            switch (op) {
                case '+': res = num1 + num2; break;
                case '-': res = num1 - num2; break;
                case '*': res = num1 * num2; break;
                case '/': res = num1 / num2; break;
                default:
                    snprintf(result, BUFLEN, "Error: Unknown operator");
                    goto send_back;
            }
            //Format the result as a string (e.g., "5 + 3 = 8").
            snprintf(result, BUFLEN, "%d %c %d = %d", num1, op, num2, res);
        }

    send_back:
        sendto(sock, result, strlen(result), 0, (struct sockaddr *)&client, slen);
        //Send the result back to the client via UDP.
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
