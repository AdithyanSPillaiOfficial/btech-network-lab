#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <string.h>
#include <fcntl.h>
int main(int argc, char *argvn)
{
    int socket_desc, new_socket, c;
    char filename[2000], message[2000];
    FILE *fp;
    struct sockaddr_in server, client;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    printf("socket created\n");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("bind failed");
        return (1);
    }
    puts("bind done");
    // Listen
    listen(socket_desc, 3);
    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
    if (new_socket < 0)
    {
        perror("accept failed");
    }

    puts("Connection accepted");
    while (1)
    {
        recv(new_socket, filename, 2000, 0);
        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            strcpy(message, "File Not Found\r\n");
            send(new_socket, message, 2000, 0);
            strcpy(message, "EOF");
        }
        else
        {
            while (fgets(message, 2000, fp))
            {
                send(new_socket, message, 2000, 0);
                puts(message);
            }
            fclose(fp);
        }
        strcpy(message, "EOF");
        send(new_socket, message, 2000, 0);
    }
    return 0;
}