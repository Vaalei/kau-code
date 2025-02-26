#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0
#define PORT 8080
#define BUFFERSIZE 104857600
#define STATIC_PATH "static"
#define MAIN_SITE "index.html"
#define NOT_AN_EXTENSION "NaMIME"

void *handle_client(void *arg);
void build_html_response(char* file_path, char* file_ext, char* response, size_t* response_len);
