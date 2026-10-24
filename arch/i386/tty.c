#include <kernel/tty.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "io.h"
#include "vga.h"

static size_t current_row;
static size_t current_column;
static uint8_t current_color;
static volatile uint16_t* vga_buffer = (uint16_t*)VGA_MEMORY;

static void disable_cursor(void) {
    outb(0x3D4, 0x0A); // Select cursor start register
    outb(0x3D5, 0x20); // Disable the cursor
}

static void disable_blinking(void) {
    (void)inb(0x3DA);                         // Make next write to 0x3C0 select register
    outb(0x3C0, 0x30);                        // Select register 0x10 but with bit 5 set to 1
    const uint8_t mode = inb(0x3C1) & ~0x08U; // Read the current state and clear bit 3
    outb(0x3C0, mode);                        // Write the mode back
}

void tty_init(void) {
    disable_cursor();
    disable_blinking();

    current_row = 0;
    current_column = 0;
    current_color = vga_make_color(TTY_COLOR_LIGHT_GREY, TTY_COLOR_BLACK);

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = vga_make_entry(' ', current_color);
        }
    }
}

void tty_scroll(unsigned int rows) {
    if (rows > VGA_HEIGHT) {
        rows = VGA_HEIGHT;
    }

    for (size_t row = 0; row < VGA_HEIGHT - rows; row++) {
        for (size_t column = 0; column < VGA_WIDTH; column++) {
            vga_buffer[row * VGA_WIDTH + column] = vga_buffer[(row + rows) * VGA_WIDTH + column];
        }
    }

    for (size_t row = VGA_HEIGHT - rows; row < VGA_HEIGHT; row++) {
        for (size_t column = 0; column < VGA_WIDTH; column++) {
            vga_buffer[row * VGA_WIDTH + column] = vga_make_entry(' ', current_color);
        }
    }

    if (current_row >= rows) {
        current_row -= rows;
    }
    else {
        current_row = 0;
        current_column = 0;
    }
}

static void tty_newline(void) {
    if (++current_row == VGA_HEIGHT) {
        tty_scroll(1);
    }
    current_column = 0;
}

void tty_put_char_at(const char c, const uint8_t color, const size_t x, const size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    vga_buffer[index] = vga_make_entry(c, color);
}

void tty_set_fg_at(const uint8_t fg, const size_t x, const size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    const uint16_t entry = vga_buffer[index];
    const uint8_t bg = vga_color_bg(vga_entry_color(entry));
    const unsigned char glyph = vga_entry_glyph(entry);
    const uint8_t color = vga_make_color(fg, bg);
    vga_buffer[index] = vga_make_entry(glyph, color);
}

void tty_set_bg_at(const uint8_t bg, const size_t x, const size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    const uint16_t entry = vga_buffer[index];
    const uint8_t fg = vga_color_fg(vga_entry_color(entry));
    const unsigned char glyph = vga_entry_glyph(entry);
    const uint8_t color = vga_make_color(fg, bg);
    vga_buffer[index] = vga_make_entry(glyph, color);
}

void tty_set_color_at(const uint8_t color, const size_t x, const size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    const uint16_t entry = vga_buffer[index];
    const unsigned char glyph = vga_entry_glyph(entry);
    vga_buffer[index] = vga_make_entry(glyph, color);
}

void tty_set_color(const uint8_t color) {
    current_color = color;
}

void tty_put_char(const char c) {
    if (c == '\n') {
        tty_newline();
        return;
    }

    tty_put_char_at(c, current_color, current_column, current_row);
    if (++current_column == VGA_WIDTH) {
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

size_t tty_width(void) {
    return VGA_WIDTH;
}

size_t tty_height(void) {
    return VGA_HEIGHT;
}

uint8_t tty_get_color_at(const size_t x, const size_t y) {
    return vga_entry_color(vga_buffer[y * VGA_WIDTH + x]);
}

uint8_t tty_get_color(void) {
    return current_color;
}

uint8_t tty_make_color(const uint8_t fg, const uint8_t bg) {
    return vga_make_color(fg, bg);
}
