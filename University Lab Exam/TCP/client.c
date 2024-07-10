#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int sock_desc;
    struct sockaddr_in server_addr;
    char client_message[2000], server_message[2000];

    memset(client_message, '\0', sizeof(client_message));
    memset(server_message, '\0', sizeof(server_message));

    sock_desc = socket(AF_INET, SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr))<0) {
        printf("Error while connecting to the server");
        return 0;
    }
    printf("Connected to the server\n");

    printf("Enter a message to send to the server : ");
    gets(client_message);

    if(send(sock_desc, client_message, sizeof(client_message),0)<0) {
        printf("Error while sending message");
        return 0;
    }
    printf("Message sended");

    if(recv(sock_desc, server_message, sizeof(server_message),0)<0) {
        printf("Error while receiving replay");
        return 0;
    }
    printf("Replay from server : %s\n", server_message);

    close(sock_desc);

    return 0;
}