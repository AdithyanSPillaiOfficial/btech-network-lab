#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h> //inet_addr
int main(int argc, char *argv[])
{
    struct sockaddr_in si_other;
    // Create Socket
    int s, i, slen = sizeof(si_other);
    char buf[2000];
    char message[2000];
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
    }
    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(8888);
    if (inet_aton("127.0.0.1", &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    while (1)
    {
        printf("Enter Command:(date/time)\n");
        fscanf(stdin, "%s", message);
        // send the message
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *)&si_other, slen) == -1)
        {
            perror("sendto()");
        }
        // recieve a reply and print it
        // clear the buffer by filling it with null, it might have previously recieved data
        memset(buf, '\0', 2000);
        // try to recieve some data, this is a blocking call
        if (recvfrom(s, buf, 2000, 0, (struct sockaddr *)&si_other, &slen) == -1)
        {
            perror("recvfrom()");
        }
        puts(buf);
    }

    return 0;
}