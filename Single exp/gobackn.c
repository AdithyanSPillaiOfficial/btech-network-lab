#include <stdio.h>
#include <stdlib.h>
void main()
{
    int noftosend, temp2, totalack, totalsend, winsize = 8, noframes, moreframes, i;
    int receiver(int);
    int simulate(int);
    totalsend = 0, noftosend = 0, temp2 = 0, totalack = 0;
    noframes = 10;
    winsize = 8;
    moreframes = noframes;
    printf("numberof frames=%d\n", noframes);
    while (moreframes > 0)
    {
        noftosend = simulate(winsize);
        winsize -= noftosend;
        totalsend += noftosend;
        if (totalsend > noframes)
        {
            totalsend = noframes;
        }
        for (i = totalack + 1; i <= totalsend; i++)
            printf("\nSending frame %d", i);
        temp2 = receiver(noftosend);
        totalack += temp2;
        if (totalack > noframes)
            totalack = noframes;
        printf("\nacknowledgement for frame upto %d", totalack);
        moreframes -= temp2;
        totalsend = totalack;
        if (winsize <= 0)
            winsize = 8;
    }
    printf("\nend of sliding window protocol");
}
int receiver(int noftosend)
{
    int i;
    for (i = 0; i < 100; i++)
        rand();
    i = rand() % noftosend;
    return 1;
}
int simulate(int winsize)
{
    int noftosend, i;
    for (i = 0; i < 50; i++)
        noftosend = rand();
    if (noftosend == 0)
        noftosend = simulate(winsize);
    i = noftosend % winsize;
    if (i == 0)
        return winsize;
    else
        return noftosend % winsize;
}