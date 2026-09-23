struct VGA_cursor;

#include "include/kernel.h"
#include "include/gdt.h"
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
    struct VGA_cursor cursor = {1, 1};

    flush_gdt();
    terminal_write_current("[LOG] GDT Loaded", &cursor);
    terminal_write_current("[LOG] Kernel Loaded. Redirecting...", &cursor);
    delay_cycles(10000000);
    terminal_clear();

    terminal_write("BlinkOS Kernel", 1, 1);
    delay_cycles(10000000);
    terminal_clear();

    panic("Testing kernel panic. This is a test message to see if the kernel panic function works correctly.");
    while (1)
    {
      __asm__ volatile ("hlt"); // sleep kernel until a interrupt triggers 
    }
}