#pragma once
#include "kernel.h"

#define TEXT_VGA_BUFFER ((volatile unsigned char *)0xB8000)
#define GRAY_COLOR 0x07

void terminal_write(const char msg[], int x, int y);
void terminal_clear();