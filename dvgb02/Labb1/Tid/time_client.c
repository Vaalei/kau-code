#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TIME_OFFSET 2208988800U // Difference between 1900 and 1970 in seconds

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* server_ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[4];
    time_t server_time;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("invalid address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send request to server
    sendto(sockfd, buffer, sizeof(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    // Receive time from server
    recvfrom(sockfd, &server_time, sizeof(server_time), 0, NULL, NULL);

    // Convert time from network byte order
    server_time = ntohl(server_time) - TIME_OFFSET;

    // Print the time in readable format
    printf("Server time: %s", ctime(&server_time));

    close(sockfd);
    return 0;
}