#include "include/kernel.h"
#include "include/vga.h"

void cli() {
    __asm__ volatile ("cli");
}

void hlt() {
    __asm__ volatile("hlt");
}

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

    panic("ocuz abi");
    while (1)
    {
      __asm__ volatile ("hlt"); // sleep kernel until a interrupt triggers 
    }
}