#include "kernel.h"

void delay_cycles(unsigned int cycles) {
    while (cycles--)
    {
        __asm__ ("pause");
    }
    
}

void kernel_main(void) {
    char text_buffer[] = "Blink Kernel";

    for (int i = 0; text_buffer[i] != '\0'; i++) {
        TEXT_VGA_BUFFER[i * 2] = text_buffer[i];
        TEXT_VGA_BUFFER[(i * 2) + 1] = 0x07; 
    }

    delay_cycles(10000000);

    for (int i = 0; i < 2000; i++)
    {
        TEXT_VGA_BUFFER[i * 2] = ' ';
        TEXT_VGA_BUFFER[i * 2 + 1] = 0x07;
    }

    while (1)
    {
      __asm__ volatile ("hlt"); // sleep kernel until a interrupt triggers 
    }
}