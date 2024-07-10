#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    char sender[50], receiver[50];
    int i, winsize;
    printf("Enter the window size:");
    scanf("%d", &winsize);
    printf("\n sender window is expected to storemessage\n");
    printf("Enter the data to be sent:");
    // flush(stdin);
    scanf("%s", sender);
    for (i = 0; i < winsize; i++)
        receiver[i] = sender[i];
    receiver[i] = NULL;
    printf("\n window size of receiver is expanded \n");
    printf("\n Acknowledgement from receiver \n");
    for (i = 0; i < winsize; i++)
        printf("\n ack:%d", i);
    printf("\n Msg received is %s \n", receiver);
    printf("\n window size of receiver shrinked \n");
}