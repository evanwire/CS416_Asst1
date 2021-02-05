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

    void* signal_handler_frame_address = signum_address + 0xd14;

    void* main_frame_address = signal_handler_frame_address + 0x30;

    char* main_rip_address = main_frame_address - 0xc68;

    *main_rip_address -= 0xfffffffffffffff;

    // char* main_frame_rip = main_frame_address - 0x8;

    //7fffffffd82

    // *main_frame_rip -= 100;
    // void* prev_frame_stack_pointer = signum_address - 0x8;
    // printf("prev_frame_stack_pointer =\t\t %p\n", prev_frame_stack_pointer);

    // void* prev_frame_base_pointer = prev_frame_stack_pointer - 0x10;
    // printf("prev_frame_base_pointer= \t %p\n", prev_frame_base_pointer);

    // char* prev_frame_instruction_pointer = prev_frame_base_pointer + 0x8;
    // printf("prev_frame_instruction_pointer = \t %p\n", prev_frame_instruction_pointer);

    // *prev_frame_instruction_pointer += 10;

    // exit(0);

    /**
     * ITS SIGNAL HANDELR (f 1)'s RIP ADDRESS
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
