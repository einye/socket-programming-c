#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1" // Change to your friend's IP when testing remotely
#define MAX_MSG_LEN 1024
void display_menu();
void clear_screen();
int main() {
int sockfd;
struct sockaddr_in server_addr;
char send_buf[MAX_MSG_LEN], recv_buf[MAX_MSG_LEN];
socklen_t addr_len = sizeof(server_addr);
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
perror("Socket creation failed");
exit(EXIT_FAILURE);
}
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(SERVER_PORT);
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
int choice;
while (1) {
display_menu();
if (scanf("%d", &choice) != 1) {
printf("Invalid input!\n");
while (getchar() != '\n');
continue;
}
memset(send_buf, 0, sizeof(send_buf));
if (choice == 1) {
char name[50], id[20], type[10];
printf("Enter Name: ");
scanf("%s", name);
printf("Enter National ID: ");
scanf("%s", id);
printf("Enter Account Type (savings/checking): ");
scanf("%s", type);
snprintf(send_buf, sizeof(send_buf), "open %s %s %s", name, id, type);
} else if (choice == 2) {
int acc, pin;
printf("Enter Account Number: ");
scanf("%d", &acc);
printf("Enter PIN: ");
scanf("%d", &pin);
snprintf(send_buf, sizeof(send_buf), "close %d %d", acc, pin);
} else if (choice == 3) {
int acc, pin, amt;
printf("Enter Account Number: ");
scanf("%d", &acc);
printf("Enter PIN: ");
scanf("%d", &pin);
printf("Enter amount to withdraw: ");
scanf("%d", &amt);
snprintf(send_buf, sizeof(send_buf), "withdraw %d %d %d", acc, pin, amt);
} else if (choice == 4) {
int acc, pin, amt;
printf("Enter Account Number: ");
scanf("%d", &acc);
printf("Enter PIN: ");
scanf("%d", &pin);
printf("Enter amount to deposit: ");
scanf("%d", &amt);
snprintf(send_buf, sizeof(send_buf), "deposit %d %d %d", acc, pin, amt);
} else if (choice == 5) {
int acc, pin;
printf("Enter Account Number: ");
scanf("%d", &acc);
printf("Enter PIN: ");
scanf("%d", &pin);
snprintf(send_buf, sizeof(send_buf), "balance %d %d", acc, pin);
} else if (choice == 6) {
int acc, pin;
printf("Enter Account Number: ");
scanf("%d", &acc);
printf("Enter PIN: ");
scanf("%d", &pin);
snprintf(send_buf, sizeof(send_buf), "statement %d %d", acc, pin);
} else if (choice == 7) {
snprintf(send_buf, sizeof(send_buf), "exit");
sendto(sockfd, send_buf, strlen(send_buf), 0,
(struct sockaddr *)&server_addr, addr_len);
printf("Goodbye!\n");
break;
} else {
printf("Invalid choice.\n");
continue;
}
sendto(sockfd, send_buf, strlen(send_buf), 0,
(struct sockaddr *)&server_addr, addr_len);
int len = recvfrom(sockfd, recv_buf, sizeof(recv_buf) - 1, 0,
(struct sockaddr *)&server_addr, &addr_len);
if (len > 0) {
recv_buf[len] = '\0';
printf("\n--- Server Response ---\n%s\n", recv_buf);
}
printf("Press Enter to continue...");
getchar(); getchar();
}
close(sockfd);
return 0;
}
void display_menu() {
clear_screen();
printf("===== Simple Bank App (Client) =====\n");
printf("1. Open Account\n");
printf("2. Close Account\n");
printf("3. Withdraw\n");
printf("4. Deposit\n");
printf("5. Check Balance\n");
printf("6. Mini Statement\n");
printf("7. Exit\n");
printf("Choose an option: ");
}
void clear_screen() {
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}