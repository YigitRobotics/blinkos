#include "include/kernel.h"
#include "include/vga.h"

void delay_cycles(unsigned int cycles) {
    while (cycles--)
    {
        __asm__ volatile ("pause");
    }
    
}

void kernel_main(void) {
    terminal_write("BlinkOS Kernel", 1, 1);
    delay_cycles(10000000);
    terminal_clear();

    while (1)
    {
      __asm__ volatile ("hlt"); // sleep kernel until a interrupt triggers 
    }
}