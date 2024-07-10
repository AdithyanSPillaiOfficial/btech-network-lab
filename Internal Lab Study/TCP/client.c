#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock_desc;
    struct sockaddr_in server_addr;
    char client_msg[2000], server_msg[2000];

    memset(client_msg,'\0',sizeof(client_msg));
    memset(server_msg,'\0',sizeof(server_msg));

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_desc < 0) {
        printf("Failed to create socket");
        return (-1);
    }
    printf("Socket created sucessfully\n");
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sock_desc, (struct sockaddr *)&server_addr,sizeof(server_addr))<0) {
        printf("Failed to Connect");
        return(-1);
    }
    printf("Successfully connected to the server");

    printf("Enter a message to send : ");
    gets(client_msg);

    if(send(sock_desc, client_msg, sizeof(client_msg),0)<0) {
        printf("Failed to send message");
        return -1;
    }
    printf("Message sended sucessfully");

    if(recv(sock_desc, server_msg, sizeof(server_msg),0)<0){
        printf("Failed to receive message");
        return -1;
    }
    printf("Message received %s", server_msg);

    close(sock_desc);
    return 0;
}