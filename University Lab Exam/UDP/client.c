#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int socket_desc;
    struct sockaddr_in server_addr;
    char client_message[2000], server_message[2000];

    memset(client_message, '\0', sizeof(client_message));
    memset(server_message, '\0', sizeof(server_message));

    socket_desc = socket(AF_INET, SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter the message to send : ");
    gets(client_message);

    if(sendto(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr))<0) {
        printf("Failed to send Data");
        return 0;
    }
    printf("Data send sucessfully");

    if(recvfrom(socket_desc, server_message, sizeof(server_message),0, (struct sockaddr *)&server_addr, sizeof(server_addr))<0) {
        printf("Failed to receive replay");
    }
    printf("Message received : %s", server_message);
    
    close(socket_desc);
    return 0;
}