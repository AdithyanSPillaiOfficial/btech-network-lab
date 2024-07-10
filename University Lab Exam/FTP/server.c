#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main () {
    int sock_desc, client_sock, client_size;
    struct sockaddr_in server_address, client_address;
    char server_message[2000], client_message[2000];
    FILE *fp;

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(bind(sock_desc, (struct sockaddr *)&server_address, sizeof(server_address))<0) {
        printf("Unable to bind");
        return 0;
    }
    printf("Bind done");

    if(listen(sock_desc,3)<0) {
        printf("Error while listening");
    }
    printf("Listening.....\n");

    client_size = sizeof(client_address);
    client_sock = accept(sock_desc, (struct sockaddr *)&client_address, &client_size);
    if(client_sock<0) {
        printf("Error while accepting connection");
    }
    printf("Connection received. IP : %s\n PORT : %d\n", inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));

    if(recv(client_sock, client_message, sizeof(client_message),0)<0) {
        printf("Error while receiving message from the server");
        return 0;
    }
    printf("Filename accepted : %s", client_message);

    fp = fopen(client_message, "r");

    if(fp== NULL) {
        printf("File not found");
        strcpy(server_message, "File Not found");
        send(client_sock, server_message, sizeof(server_message),0);
    }
    else {
        while(fgets(server_message, sizeof(server_message), fp)){
            send(client_sock, server_message, sizeof(server_message),0);
            puts(server_message);
        }
        fclose(fp);

        strcpy(server_message, "EOF");
        send(client_sock, server_message, sizeof(server_message),0);
    }
    close(sock_desc);
    close(client_sock);
    return 0;
    
}

