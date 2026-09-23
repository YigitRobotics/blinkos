#include "../include/vga.h"

void terminal_write(const char msg[], int x, int y) {
    int index = y * 80 + x; 
    for (int i = 0; msg[i] != '\0'; i++) {
        TEXT_VGA_BUFFER[(i + index) * 2] = msg[i];
        TEXT_VGA_BUFFER[(i + index) * 2 + 1] = GRAY_COLOR;
    }
}

void terminal_write_current(const char msg[], struct VGA_cursor *vga_cursor_index) {
    terminal_write(msg, vga_cursor_index->x, vga_cursor_index->y);
    vga_cursor_index->x++;
    vga_cursor_index->y++;
}

void terminal_clear() {
    for (int i = 0; i < 2000; i++) {
        TEXT_VGA_BUFFER[i * 2] = ' ';
        TEXT_VGA_BUFFER[i * 2 + 1] = GRAY_COLOR;
    }
}