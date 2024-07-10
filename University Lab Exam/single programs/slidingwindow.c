#include <stdio.h>

int main() {
    int window_size, i;
    char sender[50], receiver[50];

    printf("Enter the size of the window : ");
    scanf("%d", &window_size);

    printf("Enter message to be send : ");
    scanf("%s", sender);

    for(i=0;i<window_size;i++){
        receiver[i] = sender[i];
    }
    receiver[i] = NULL;

    printf("Acknowledgement for \n");
    for(i=0;i<window_size;i++){
        printf("Ack:%d\n",i);
    }

    printf("Message received %s", receiver);
}