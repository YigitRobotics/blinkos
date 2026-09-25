#include "../include/keyboard.h"
#include "../include/io.h"
#include "../include/vga.h"

static const char keyboard_scancode_map[128] = {
    [2] = '1', [3] = '2', [4] = '3', [5] = '4', [6] = '5',
    [7] = '6', [8] = '7', [9] = '8', [10] = '9', [11] = '0',
    [16] = 'q', [17] = 'w', [18] = 'e', [19] = 'r', [20] = 't',
    [21] = 'y', [22] = 'u', [23] = 'i', [24] = 'o', [25] = 'p',
    [30] = 'a', [31] = 's', [32] = 'd', [33] = 'f', [34] = 'g',
    [35] = 'h', [36] = 'j', [37] = 'k', [38] = 'l',
    [44] = 'z', [45] = 'x', [46] = 'c', [47] = 'v', [48] = 'b',
    [49] = 'n', [50] = 'm', [57] = ' '
};


void keyboard_interrupt_c() {
    static struct VGA_cursor cursor = {9, 1};
    uint8_t scancode = inb(0x60);
    outb(0x20, 0x20);

    if (scancode & 0x80 || keyboard_scancode_map[scancode] == '\0') {
        return;
    }
    
    char output_attribute[2] = { keyboard_scancode_map[scancode], '\0' };
    terminal_write_current_x(output_attribute, &cursor);
}