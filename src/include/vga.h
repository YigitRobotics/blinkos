#pragma once
#include "kernel.h"

#define TEXT_VGA_BUFFER ((volatile unsigned char *)0xB8000)
#define GRAY_COLOR 0x07

struct VGA_cursor
{
    int x;
    int y;
};

void terminal_write(const char msg[], int x, int y);
void terminal_clear();
void terminal_write_current(const char msg[], struct VGA_cursor *vga_cursor_index);
