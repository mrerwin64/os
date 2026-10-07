#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/tty.h>
#include "vga.h"

static size_t tty_row;
static size_t tty_column;
static uint8_t tty_color;
static volatile uint16_t* tty_buffer = (uint16_t*)VGA_MEMORY;

void tty_init(void)
{
    tty_row = 0;
    tty_column = 0;
    tty_color = vga_entry_color(TTY_COLOR_LIGHT_GREY, TTY_COLOR_BLACK);

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            tty_buffer[index] = vga_entry(' ', tty_color);
        }
    }
}

void tty_put_char_at(const char c, const uint8_t color, const size_t x, const size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    tty_buffer[index] = vga_entry(c, color);
}

void tty_put_char(const char c)
{
    if (c == '\n')
    {
        if (++tty_row == VGA_HEIGHT) {
            tty_row = 0;
        }
        tty_column = 0;
        return;
    }
    
    tty_put_char_at(c, tty_color, tty_column, tty_row);
    if (++tty_column == VGA_WIDTH) {
        tty_column = 0;
        if (++tty_row == VGA_HEIGHT)
            tty_row = 0;
    }
}

void tty_write(const char* data, const size_t size)
{
    for (size_t i = 0; i < size; i++) {
        tty_put_char(data[i]);
    }
}

void tty_write_string(const char* data)
{
    tty_write(data, strlen(data));
}
