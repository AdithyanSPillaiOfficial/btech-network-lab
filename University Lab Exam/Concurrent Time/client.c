#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sock_desc, client_sock;
    struct sockaddr_in server_addr;
    char client_message[2000], server_message[2000];
    socklen_t sock_size;

    memset(client_message, '\0', sizeof(client_message));
    memset(server_message, '\0', sizeof(server_message));

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    printf("Enter Command (Date/Time) : ");
    scanf("%s",client_message);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock_size = sizeof(server_addr);
    if(sendto(sock_desc, client_message, sizeof(client_message),0, (struct sockaddr *)&server_addr, sizeof(server_addr))<0) {
        printf("Sending Failed");
        return 0;
    }
    printf("Message send\n");

    if(recvfrom(sock_desc, server_message, sizeof(server_message),0, (struct sockaddr *)&server_addr, &sock_size)<0) {
        printf("Unable to receive message");
        return 0;
    }
    printf("Message received : %s",server_message);

    close(sock_desc);
    return 0;
}