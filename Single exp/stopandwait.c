#include <stdio.h> #include<stdlib.h>
int ack()
{
    int k;
    k = rand();
    if (k % 2 == 0)
        return 1;
    else
        return 0;
}
void main()
{
    int n, i, test;
    printf("enter the no:of packet you need to stimulate\n");
    scanf("%d", &n);
    for (i = 0; i <= n; i++)
    {
    x:
        test = ack();
        printf("%d\n", test);
        if (test == 1)
        {
            printf("success ack received for pack -%d- sending next packet\n", i);
        }
        else
        {
            printf("Failed ack not received for pack %d- sending packet again\n", i);
            goto x;
        }
    }
}