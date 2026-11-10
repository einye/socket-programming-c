//CONNECTION ORIENTED SERVER CALCULATOR PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 12345
#define BUFLEN 512

int main() {
    //Set up Winsock for network communication.
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);
    char buf[BUFLEN], result[BUFLEN];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    //Create a TCP socket.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    //Configure server address (IP: any, Port: 12345).
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    //Bind socket to the server address and listen for connections.
    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 5);

    printf("TCP server is running on port %d...\n", PORT);

    while (1) {
        //Accept a new client connection.
        client_fd = accept(server_fd, (struct sockaddr *)&client, &client_len);
        
        //Receive an expression string (e.g., "5 + 3") from the client.
        memset(buf, 0, BUFLEN);
        recv(client_fd, buf, BUFLEN, 0);

        printf("Received: %s\n", buf);

        int num1, num2;
        char op;
        int consumed = sscanf(buf, "%d %c %d", &num1, &op, &num2);

        //If parsing fails (fewer than 3 components), prepare error message: "Invalid format".
        if (consumed != 3) {
            snprintf(result, BUFLEN, "Error: Invalid format");
        } 
        
        //If operator is division (/) and num2 is 0, prepare error message: "Division by zero". 
        else if (op == '/' && num2 == 0) {
            snprintf(result, BUFLEN, "%d / 0 = Error: Division by zero", num1);
        } else {
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
            ////Format the result as a string (e.g., "5 + 3 = 8")
            snprintf(result, BUFLEN, "%d %c %d = %d", num1, op, num2, res);
        }

    send_back:
        
        //Send the result back to the client over the TCP connection
        send(client_fd, result, strlen(result), 0);
        closesocket(client_fd);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}
