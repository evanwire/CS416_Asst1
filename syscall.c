/* syscall.c
 *
 * Group Members Names and NetIDs:
 *   1. Evan Wireman - emw160
 *   2. Reagan McFarland - rpm141
 *
 * ILab Machine Tested on: ilab1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>                                                                                
#include <sys/syscall.h>
#include <unistd.h>

double avg_time = 0;

int main(int argc, char *argv[]) {

    /* Implement Code Here */

    // Remember to place your final calculated average time
    // per system call into the avg_time variable

    struct timeval t1, t2;
    double elapsedTime;

    FILE *fp;
    fp = fopen ("temp.txt", "w");

    int i;
    for(i = 0; i < 5000; i++){
        gettimeofday(&t1, NULL);
        
        //Need to include unistd.h to run the syscall() function
        syscall(SYS_write, fp, "Hello World", 12);
        
        gettimeofday(&t2, NULL);

        elapsedTime = (t2.tv_usec - t1.tv_usec); // sec to microseconds
        avg_time += elapsedTime;
    }

    avg_time = avg_time / 5000.0;
    
    fclose(fp);
    remove("temp.txt");

    printf("Average time per system call is %f microseconds\n", avg_time);

    return 0;
}
