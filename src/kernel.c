struct VGA_cursor;

#include "include/kernel.h"
#include "include/gdt.h"
#include "include/vga.h"
#include "include/interrupt.h"
#include "include/io.h"

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

void test_io() {
    char testing[] = "Testing I/O Ports";
    for (int i = 0; testing[i] != '\0'; i++) {
        outb(0xE9, testing[i]); // qemu debug console port
    }
}

void kernel_main(void) {
    struct VGA_cursor cursor = {1, 1};

    flush_gdt();
    terminal_write_current("[LOG] GDT Loaded", &cursor);
    install_idt();
    terminal_write_current("[LOG] IDT Loaded", &cursor);

    terminal_write_current("[LOG] Kernel Loaded. Redirecting...", &cursor);
    delay_cycles(10000000);
    terminal_clear();

    test_io();
    terminal_write("BlinkOS Kernel BY YigitRobotics", 1, 1, GREEN_COLOR);
    delay_cycles(10000000);
    terminal_clear();

    panic("Testing kernel panic. This is a test message to see if the kernel panic function works correctly.");
    while (1)
    {
      __asm__ volatile ("hlt"); // sleep kernel until a interrupt triggers 
    }
}