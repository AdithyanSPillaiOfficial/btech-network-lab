#include <stdio.h>
#include <stdlib.h>

int ack()
{
    int k = rand();
    if (k % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int n, k, i;
    printf("Enter the no of packets you need to simulate : ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
    x:
        k = ack();
        if (k == 1)
        {
            printf("sucess ack received for %d packet\n", i);
        }
        else
        {
            printf("ack not received for %d packet. Resending packet\n", i);
            goto x;
        }
    }
}