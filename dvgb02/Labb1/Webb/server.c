#include "server.h"

int main(){
    int server_fd;
    struct sockaddr_in server_addr;
    int opt = TRUE;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // maybe, såg på nätet, binder till en ip?
    // inet_aton("63.161.169.137", &server_addr.sin_addr.s_addr);

    // Add SO_REUSEADDR to be able to reuse socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt error");
        exit(EXIT_FAILURE);
    } 

    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("socket bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening on the socket, max 5 clients at once
    if (listen(server_fd, 5) < 0) {
        perror("socket listen failed");
        exit(EXIT_FAILURE);
    }

    // Main loop
    while (TRUE) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int *client_fd = malloc(sizeof(int));

        if ((*client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
            perror("socket accept client failed");
            continue;
        }

        // Create a thread that handles the client, the server continues running and can accept more clients
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *)client_fd);
        pthread_detach(thread_id);
    }

    return 0;
}

void *handle_client(void *arg) {
    char* start;
    char* end;
    char file_name[32];
    char* file_ext;
    char* dot;
    int client_fd = *((int *)arg);
    char *buffer = (char *)malloc(BUFFERSIZE);

    ssize_t bytes_recieved = recv(client_fd, buffer, BUFFERSIZE, 0);

    // If there is any content in the request
    if (bytes_recieved > 0) {
        // Find requested website filename
        if (!(start = strstr(buffer, "GET ")) ||
            !(end = strstr(buffer, " HTTP/1.1"))) {
                perror("did not find start or end of address");
                exit(EXIT_FAILURE);
            }
        strncpy(file_name, start + 4, end - start - 4);

        file_name[end - start - 4] = '\0';

        // Find file extention
        if ((dot = strstr(file_name, "."))) {
            file_ext = dot + 1;
        }
        else {
            file_ext = NOT_AN_EXTENSION;
        }
        
        
        // Build HTTP response
        char* response = (char *)malloc(BUFFERSIZE);
        size_t response_len;
        build_html_response(file_name, file_ext, response, &response_len);

        // Send HTTP response
        send(client_fd, response, response_len, 0);

        free(response);
    }

    close(client_fd);
    free(arg);
    free(buffer);
    return NULL;
}

void build_html_response(char* file_name, char* file_ext, char* response, size_t *response_len) {
    char* mime_type; 
    // Get file path
    char* path = (char *)malloc(BUFFERSIZE * sizeof(char *));
    strcpy(path, STATIC_PATH);
    strcat(path, file_name);

    // build HTTP header
    char *header = (char *)malloc(BUFFERSIZE*sizeof(char *));

    // open file
    int file_fd = open(path, O_RDONLY);
    
    // Get file size
    struct stat file_stat;
    fstat(file_fd, &file_stat);
    off_t file_size = file_stat.st_size;

    // file_fd = -1 if the file does not exist
    if (file_fd == -1 || strcmp(file_name, "/") == 0) {
        // Generate 404 Not found header
        snprintf(response, BUFFERSIZE, 
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "404 not found"
        );
        *response_len = strlen(response);
        free(path);
        free(header);
        return;
    }

    // Get correct MIME from extension
    if (strcmp(file_ext, "jpg") == 0) mime_type = "image/jpeg";
    else if (strcmp(file_ext, "html") == 0) mime_type = "text/html";
    else {
        perror("file extension not supported");
        return;
    }
    printf("filemime: %s\n", mime_type);

    // Create 200 ok header
    snprintf(header, BUFFERSIZE, 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "\r\n",
        mime_type,
        file_size
    );

    // Copy header to response
    strncpy(response, header, strlen(header));
    *response_len = strlen(header);

    ssize_t bytes_read;

    while ((bytes_read = read(file_fd, response + *response_len, BUFFERSIZE - *response_len)) > 0) {
        *response_len += bytes_read;
    }

    free(path);
    free(header);
    close(file_fd);
    return;
}



