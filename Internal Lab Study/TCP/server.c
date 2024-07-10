#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock_desc, client_desc, client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_msg[2000], client_msg[2000];

    memset(client_msg, '\0', sizeof(client_msg));
    memset(server_msg, '\0', sizeof(server_msg));

    sock_desc = socket(AF_INET,SOCK_STREAM, 0);
    if(sock_desc < 0) {
        printf("Failed to create socket");
        return -1;
    } 
    printf("Socket created sucessfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        printf("Failed to bind");
        return -1;
    }
    printf("Binded Sucessfully\n");

    if(listen(sock_desc, 1)<0){
        printf("Error while listening\n");
        return -1;
    }
    printf("Listening....");

    client_size = sizeof(client_addr);
    client_desc = accept(sock_desc, (struct sockaddr *)&client_addr, &client_size);

    if(client_desc<0){
        printf("Error while accepting");
        return -1;
    }
    printf("Connected to the IP address %s and port %d",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

    if(recv(client_desc, client_msg, sizeof(client_msg),0)<0){
        printf("Error while receiving data");
        return -1;
    }
    printf("Message from client : %s \n",client_msg);

    printf("Enter a responce to client : ");
    gets(server_msg);

    if(send(client_desc, server_msg, sizeof(server_msg),0)<0){
        printf("Error while sending responce : ");
        return -1;
    }
    printf("Responce sended sucessfully");

    close(client_desc);
    close(sock_desc);
    return 0;

}