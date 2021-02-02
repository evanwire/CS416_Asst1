#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Part 1 - Step 2 to 4: Do your tricks here
 * Your goal must be to change the stack frame of caller (main function)
 * such that you get to the line after "r2 = *( (int *) 0 )"
 */

int count = 0;

void segment_fault_handler(int signum) {
    count++;
    printf("I am slain!\n");
 
    /* Implement Code Here */
    void* signum_address = &signum;
    printf("signum_addrress =\t %p\n", signum_address);

    void* prev_frame_stack_pointer = signum_address + 0xD44;
    printf("prev_frame_stack_pointer =\t\t %p\n", prev_frame_stack_pointer);

    void* prev_frame_base_pointer = prev_frame_stack_pointer - 0x10;
    printf("prev_frame_base_pointer= \t %p\n", prev_frame_base_pointer);

    char* prev_frame_instruction_pointer = prev_frame_base_pointer + 0x8;
    printf("prev_frame_instruction_pointer = \t %p\n", prev_frame_instruction_pointer);

    // exit(0);

    /**
     * 
     * 
     * 0x7fffffffe490 = prev frame sp
     * 0x7fffffffd75c = signum
     * 
     * end of instruction is at 0x7fffffffe488, we want to be at 
     */
    if(count > 5) exit(0);
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
