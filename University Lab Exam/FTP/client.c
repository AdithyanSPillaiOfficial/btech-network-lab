#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int sock_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    FILE *fp;

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connect error");
        return 0;
    }
    printf("Connection sucess");

    do
    {
        printf("Enter Filename : ");
        gets(client_message);
        if (send(sock_desc, client_message, sizeof(client_message), 0) < 0)
        {
            printf("Error while sending");
            continue;
        }
        printf("Send sucess");

        fp = fopen("received.txt", "w");

        while (recv(sock_desc, server_message, sizeof(server_message), 0))
        {
            if (strcmp(server_message, "EOF"))
            {
                fputs(server_message, fp);
                puts(server_message);
            }
            else {
                // fputs("EOF", fp);
                fclose(fp);
                break;
            }
        }

    } while (1);

    close(sock_desc);
    return 0;
}