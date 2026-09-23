#pragma once
#include <stdint.h>

void idt_set_gate(uint8_t num, uint32_t base);
extern void idt_load(uint32_t idt_ptr_addr);
void install_idt();

struct idt_entry
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern uint64_t idt[256];
extern struct idt_entry idt_ptr;