#include <time.h>
#include <stdio.h>
 
double time1, timedif;        
 
int main(void)
{
    int  i;
 
    time1 = (double) clock();            /* get initial time */
    time1 = time1 / CLOCKS_PER_SEC;      /*    in seconds    */
 
    /* running the FOR loop 10000 times */
    for (i=0; i<10000; i++);
 
    /* call clock a second time */
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("The elapsed time is %lf seconds\n", timedif);
}
