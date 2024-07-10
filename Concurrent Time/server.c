#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h> //inet_addr
int main(int argc, char *argv[])
{
    char message[2000];
    struct sockaddr_in si_me, si_other;
    int socket_desc, slen = sizeof(si_other), recv_len, i;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    si_me.sin_family = AF_INET;
    si_me.sin_addr.s_addr = INADDR_ANY;
    si_me.sin_port = htons(8888);
    if (bind(socket_desc, (struct sockaddr *)&si_me, sizeof(si_me)) < 0)
    {
        puts("bind failed");
    }
    puts("bind done");
    // Keep listening for data
    while (1)
    {
        printf("Waiting for data......\n");
        fflush(stdout);
        strcpy(message, "");
        memset(message, '\0', 2000);
        // try to recieve some data, this is a blocking call
        if ((recv_len = recvfrom(socket_desc, message, 2000, 0, (struct sockaddr *)&si_other, &slen)) == -1)
        {
            perror("recvfrom()");
        }
        // Checking Commands
        if (strcmp(message, "date") == 0)
        {
            
            // sprintf(s,"%d",i);
            sprintf(message, "Date: %d-%d-%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
            // printf("Time: %d:%d:%d\n",tm.tm_hour,tm.tm_min,tm.tm_sec);
        }
        else if (strcmp(message, "time") == 0)
        {
            t = time(NULL);
            tm = *localtime(&t);
            // sprintf(s,"%d",i);
            // sprintf("Date: %d-%d-%d\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
            sprintf(message, "Time: %d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
        puts(message);
        // now reply the client with the same data
        if (sendto(socket_desc, message, 2000, 0, (struct sockaddr *)&si_other, slen) == -1)
        {
            perror("sendto()");
        }
    }
    // close(socket_desc);
    return 0;
}