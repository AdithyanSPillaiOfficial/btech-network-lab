#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main() {
    int sock_desc, client_sock;
    socklen_t client_size;
    struct sockaddr_in server_address, client_address;
    char server_message[2000], client_message[2000];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_sock = bind(sock_desc, (struct sockaddr *)&server_address, sizeof(server_address));
    if(client_sock < 0) {
        printf("Bind failed");
        return 0;
    }
    printf("Bind Done\n");

    client_size = sizeof(client_address);
    if(recvfrom(sock_desc, client_message, sizeof(client_message),0, (struct sockaddr *)&client_address, &client_size)<0) {
        printf("Failed to receive");
        return 0;
    }
    printf("Message received :%s",client_message);
    if(strcmp(client_message, "Date") == 0) {
        sprintf(server_message, "Date : %d/%d/%d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    }
    else if(strcmp(client_message, "Time") == 0) {
        sprintf(server_message, "Time : %d:%d:%d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    else {
        sprintf(server_message, "Invalid Command\n");
    }

    if(sendto(sock_desc, server_message, sizeof(server_message), 0, (struct sockaddr *)&client_address, sizeof(client_address))<0) {
        printf("Failed to send message");
        return 0;
    }
    printf("Message send \n");

    close(sock_desc);
    close(client_sock);

    return 0;

}