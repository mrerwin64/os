#include <kernel/tty.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "vga.h"

static size_t tty_row;
static size_t tty_column;
static uint8_t tty_color;
static volatile uint16_t* tty_buffer = (uint16_t*)VGA_MEMORY;

void tty_init(void) {
    __asm__ volatile("outb %0, %1" : : "a"((uint8_t)0x0A), "Nd"((uint16_t)0x3D4)); // Select cursor start register
    __asm__ volatile("outb %0, %1" : : "a"((uint8_t)0x20), "Nd"((uint16_t)0x3D5)); // Disable the cursor

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

void tty_scroll(unsigned int rows) {
    if (rows > VGA_HEIGHT) {
        rows = VGA_HEIGHT;
    }

    for (size_t row = 0; row < VGA_HEIGHT - rows; row++) {
        for (size_t column = 0; column < VGA_WIDTH; column++) {
            tty_buffer[row * VGA_WIDTH + column] = tty_buffer[(row + rows) * VGA_WIDTH + column];
        }
    }

    for (size_t row = VGA_HEIGHT - rows; row < VGA_HEIGHT; row++) {
        for (size_t column = 0; column < VGA_WIDTH; column++) {
            tty_buffer[row * VGA_WIDTH + column] = vga_entry(' ', tty_color);
        }
    }

    if (tty_row >= rows) {
        tty_row -= rows;
    }
    else {
        tty_row = 0;
        tty_column = 0;
    }
}

static void tty_newline(void) {
    if (++tty_row == VGA_HEIGHT) {
        tty_scroll(1);
    }
    tty_column = 0;
}

void tty_put_char_at(const char c, const uint8_t color, const size_t x, const size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    tty_buffer[index] = vga_entry(c, color);
}

void tty_put_char(const char c) {
    if (c == '\n') {
        tty_newline();
        return;
    }

    tty_put_char_at(c, tty_color, tty_column, tty_row);
    if (++tty_column == VGA_WIDTH) {
        tty_newline();
    }
}

void tty_write(const char* data, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        tty_put_char(data[i]);
    }
}

void tty_write_string(const char* data) {
    tty_write(data, strlen(data));
}
