#pragma once

// ADDED: kernel panic function

void panic(const char *msg);
void delay_cycles(unsigned int cycles);
void cli();
void hlt();