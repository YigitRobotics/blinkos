#include "kernel.h"

void kernel_main(void) {
    char text_buffer[] = "Welcome to vga buffer!";

    for (int i = 0; text_buffer[i] != '\0'; i++) {
        TEXT_VGA_BUFFER[i * 2] = text_buffer[i];
        TEXT_VGA_BUFFER[(i * 2) + 1] = 0x07;  
    }

    while (1)
    {
        
    }
}