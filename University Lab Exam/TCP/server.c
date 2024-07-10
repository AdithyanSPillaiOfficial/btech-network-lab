#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];

    memset(client_message,'\0',sizeof(client_message));
    memset(server_message, '\0', sizeof(server_message));

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        printf("Bind Failed");
        return 0;
    }
    printf("Bind Done\n");

    if (listen(socket_desc,1) < 0 ){
        printf("Error While listening");
        return 1;
    }
    printf("Listening....\n");

    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);
    if(client_sock<0){
        printf("Failed to accept connection\n");
        return 0;
    }
    printf("Connection Accepted\n");
    printf("IP Address : %s \n port : %d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

    if(recv(client_sock, client_message, sizeof(client_message),0)<0) {
        printf("Error while receiving message from the client");
    }
    printf("Message from client : %s\n", client_message);

    printf("Enter a message to send as reply : ");
    gets(server_message);

    if(send(client_sock, server_message, sizeof(server_message),0)<0) {
        printf("Error while sending message");
        return 0;
    }
    printf("Message Sended\n");
    close(client_sock);
    close(socket_desc);

    return 0;
}