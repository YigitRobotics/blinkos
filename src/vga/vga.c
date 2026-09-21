#include "../include/vga.h"

void terminal_write(const char msg[], int x, int y) {
    int index = y * 80 + x; 
    for (int i = 0; msg[i] != '\0'; i++) {
        TEXT_VGA_BUFFER[(i + index) * 2] = msg[i];
        TEXT_VGA_BUFFER[(i + index) * 2 + 1] = GRAY_COLOR;
    }
}

void terminal_clear() {
    for (int i = 0; i < 2000; i++) {
        TEXT_VGA_BUFFER[i * 2] = ' ';
        TEXT_VGA_BUFFER[i * 2 + 1] = GRAY_COLOR;
    }
}