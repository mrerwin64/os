#ifndef OS_VGA_H
#define OS_VGA_H

#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

static inline __attribute__((unused)) uint8_t vga_make_color(const uint8_t fg, const uint8_t bg) {
    return (uint8_t)(fg | (unsigned int)bg << 4U);
}

static inline __attribute__((unused)) uint16_t vga_make_entry(const unsigned char glyph, const uint8_t color) {
    return (uint16_t)(glyph | (unsigned int)color << 8U);
}

static inline __attribute__((unused)) uint8_t vga_entry_glyph(const uint16_t entry) {
    return entry & 0x00FFU;
}

static inline __attribute__((unused)) uint8_t vga_entry_color(const uint16_t entry) {
    return entry >> 8U;
}

static inline __attribute__((unused)) uint8_t vga_color_fg(const uint8_t color) {
    return color & 0x0FU;
}

static inline __attribute__((unused)) uint8_t vga_color_bg(const uint8_t color) {
    return color >> 4U;
}

#endif // OS_VGA_H
