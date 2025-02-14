#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#define TIME_OFFSET 2208988800U // Difference between 1900 and 1970 in seconds
#define BUFFER_S 1024

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[1]);
    int sock_fd;
    struct sockaddr_in server_addr, client_adr;
    socklen_t addr_len = sizeof(client_adr);
    char buffer[BUFFER_S];
    time_t current_time;

    // Create UDP socket
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the socket to the port
    if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind fail");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // Receive request from client
        recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_adr, &addr_len);

        // Get current time
        current_time = time(NULL) + TIME_OFFSET;

        // Convert time to network byte order
        current_time = htonl(current_time);

        // Send time to client
        sendto(sock_fd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&client_adr, addr_len);
        printf("Data sent: %ld\n", current_time);
    }

    close(sock_fd);
    return 0;
}