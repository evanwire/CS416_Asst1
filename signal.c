#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Part 1 - Step 2 to 4: Do your tricks here
 * Your goal must be to change the stack frame of caller (main function)
 * such that you get to the line after "r2 = *( (int *) 0 )"
 * 
 * Group Members Names and NetIDs:
 *   1. Evan Wireman - emw160
 *   2. Reagan McFarland - rpm141
 *
 * ILab Machine Tested on: ilab1
 *
 */
 

void segment_fault_handler(int signum) {
    printf("I am slain!\n");
 
    /* Implement Code Here */
    void* signum_address = &signum;

    void* signal_handler_frame_address = signum_address + 0xd14;

    void* main_frame_address = signal_handler_frame_address + 0x30;

    char* main_rip_address = main_frame_address - 0xc68;

    *main_rip_address += 0x2;
}

int main(int argc, char *argv[]) {

    int r2 = 0;

    /* Part 1 - Step 1: Registering signal handler */
    /* Implement Code Here */
    signal(SIGSEGV, segment_fault_handler);

    // trying to derference 0x0 which is null, resulting in a seg fault
    r2 = *( (int *) 0 ); // This will generate segmentation fault

    printf("I live again!\n");

    return 0;
}
