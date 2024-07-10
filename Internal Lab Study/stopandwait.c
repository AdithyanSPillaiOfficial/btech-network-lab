#include <stdio.h>
#include <stdlib.h>
int ack() {
    int k;
    k = rand();
    if(k%2 == 0){
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int num, i, status;
    printf("Enter the number of packets to send : ");
    scanf("%d",&num);
    for (i=0;i<num; i++){
        x:
            status = ack();
            if(status == 1){
                printf("Packet %d sended sucessfully, sending next packet\n",i);
            }
            else {
                printf("Sending of %d packet failed, resending the packet\n",i);
                goto x;
            }
    }
}