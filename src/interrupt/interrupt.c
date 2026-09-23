#include "../include/interrupt.h"
#include "../include/kernel.h"
#include "../include/vga.h"
#include <stdint.h>

uint64_t idt[256];
struct idt_entry idt_ptr;

void idt_set_gate(uint8_t num, uint32_t base) {
    uint64_t entry = 0;
    
    entry |= (base & 0xFFFF0000ULL) << 32; // Base High (Bit 48..63)
    entry |= (0x8E00ULL) << 32;            // Flags (Bit 40..47)
    entry |= (0x080000ULL);                // Segment Selector = 0x08 (Code Segment)
    entry |= (base & 0x0000FFFFULL);       // Base Low (Bit 0..15)

    idt[num] = entry;
}

void install_idt() {
    idt_ptr.limit = (sizeof(uint64_t) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt;

    for (int i = 0; i < 256; i++) {
        idt[i] = 0;
    }

    idt_load((uint32_t)&idt_ptr);
}