#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h> // for strncasecmp
#define PORT 8888
#define BUFFER_SIZE 1024
void process_request(char *request, char *response) {
if (strncasecmp(request, "balance", 7) == 0) {
sprintf(response, "Your balance is Ksh 2000");
} else if (strncasecmp(request, "deposit", 7) == 0) {
sprintf(response, "Deposited Ksh 500 successfully");
} else if (strncasecmp(request, "withdraw", 8) == 0) {
sprintf(response, "Withdrawn Ksh 1000 successfully");
} else if (strncasecmp(request, "open", 4) == 0) {
sprintf(response, "Account opened successfully");
} else if (strncasecmp(request, "close", 5) == 0) {
sprintf(response, "Account closed successfully");
} else if (strncasecmp(request, "statement", 9) == 0) {
sprintf(response, "Mini statement: Last 3 transactions...");
} else if (strncasecmp(request, "exit", 4) == 0) {
sprintf(response, "Goodbye!");
} else {
sprintf(response, "Unknown request");
}
}
int main() {
int sockfd;
char buffer[BUFFER_SIZE];
char response[BUFFER_SIZE];
struct sockaddr_in servaddr, cliaddr;
socklen_t len;
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);
if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
perror("bind failed");
exit(EXIT_FAILURE);
}
printf("✅ UDP Bank Server running on port %d...\n", PORT);
while (1) {
len = sizeof(cliaddr);
int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
(struct sockaddr *)&cliaddr, &len);
buffer[n] = '\0';
printf("📥 Client: %s\n", buffer);
process_request(buffer, response);
sendto(sockfd, response, strlen(response), 0,
(const struct sockaddr *)&cliaddr, len);
}
close(sockfd);
return 0;
}
