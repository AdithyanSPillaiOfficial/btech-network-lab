#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sock_desc, client_sock;
    struct sockaddr_in server_addr, client_addr;
    char client_message[2000], server_message[2000];
    socklen_t addr_size;

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_sock = bind(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(client_sock<0){
        printf("Bind failed");
        return 0;
    }
    printf("Bind done\n");

    addr_size = sizeof(client_addr);
    if(recvfrom(sock_desc, client_message, sizeof(client_message),0, (struct sockaddr *)&client_addr, &addr_size)<0){
        printf("Error while receiving data");
        return 0;
    }
    printf("Data received : %s", client_message);

    printf("Enter data to send as replay : ");
    gets(server_message);

    if(sendto(sock_desc, server_message, sizeof(server_message),0, (struct sockaddr *)&client_addr, sizeof(client_addr))<0) {
        printf("Error while sending data");
        return 0;
    }
    printf("Data send");

    close(sock_desc);
    close(client_sock);

    return 0;
}