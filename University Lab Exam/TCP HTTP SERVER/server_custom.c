#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

char folder[50] = "public";

void handle_client(int client_socket, struct sockaddr_in client_addr) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, BUFFER_SIZE - 1);

    // Extracting client IP address
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);

    // Extracting request line (method, URI, HTTP version)
    char method[10], uri[100], http_version[10];
    sscanf(buffer, "%s %s %s", method, uri, http_version);

    // Print request line
    printf("Request from IP: %s\n", client_ip);
    printf("Method: %s, URI: %s, HTTP Version: %s\n", method, uri, http_version);

    // Print headers
    char *header_line = strtok(buffer, "\r\n");
    while (header_line != NULL) {
        if (strstr(header_line, "X-Username: ") != NULL) {
            printf("Username: %s\n", header_line + 12);
        } else {
            printf("Header: %s\n", header_line);
        }
        header_line = strtok(NULL, "\r\n");
    }

    printf("\n\n------------------------------------------------------------\n\n");

    const char *header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n";

    char filepath[100];
    snprintf(filepath, sizeof(filepath), "%s/home.html", folder);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("fopen");
        close(client_socket);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *html_content = malloc(file_size + 1);
    fread(html_content, 1, file_size, file);
    fclose(file);
    html_content[file_size] = '\0';

    send(client_socket, header, strlen(header), 0);
    send(client_socket, html_content, file_size, 0);

    free(html_content);
    close(client_socket);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        strcpy(folder, argv[1]);
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) == -1) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on http://localhost:%d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }
        handle_client(client_socket, client_addr);
    }

    close(server_socket);
    return 0;
}
