#include "../include/vga.h"
#include "../include/kernel.h"
#include <stdint.h>

void terminal_write(const char msg[], int x, int y, uint8_t color) {
    int index = y * 80 + x; 
    for (int i = 0; msg[i] != '\0'; i++) {
        TEXT_VGA_BUFFER[(i + index) * 2] = msg[i];
        TEXT_VGA_BUFFER[(i + index) * 2 + 1] = color;
    }
}

void terminal_write_current(const char msg[], struct VGA_cursor *vga_cursor_index) {
    terminal_write(msg, vga_cursor_index->x, vga_cursor_index->y, GRAY_COLOR);
    vga_cursor_index->x++;
    vga_cursor_index->y++;
}

void terminal_clear() {
    for (int i = 0; i < 2000; i++) {
        TEXT_VGA_BUFFER[i * 2] = ' ';
        TEXT_VGA_BUFFER[i * 2 + 1] = GRAY_COLOR;
    }
}