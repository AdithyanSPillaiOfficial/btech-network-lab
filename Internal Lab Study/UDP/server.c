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

    sock_desc = socket(AF_INET,SOCK_DGRAM, 0);
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


    if(recvfrom(sock_desc, client_msg, sizeof(client_msg), 0, NULL, NULL)<0){ // Changed recvfrom arguments
        printf("Error while receiving data");
        return -1;
    }
    printf("Message from client : %s \n",client_msg);

    printf("Enter a responce to client : ");
    gets(server_msg);

    if(sendto(sock_desc, server_msg, strlen(server_msg) + 1, 0, (struct sockaddr *)&client_addr, sizeof(client_addr))<0){ // Corrected buffer size
        printf("Error while sending responce : ");
        return -1;
    }
    printf("Responce sended sucessfully");

    close(client_desc);
    close(sock_desc);
    return 0;

}