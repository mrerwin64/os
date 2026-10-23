#ifndef OS_VGA_H
#define OS_VGA_H

#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

static inline __attribute__((unused)) uint8_t vga_entry_color(const uint8_t fg, const uint8_t bg) {
    return (uint8_t)(fg | (unsigned int)bg << 4U);
}

static inline __attribute__((unused)) uint16_t vga_entry(const unsigned char uc, const uint8_t color) {
    return (uint16_t)(uc | (unsigned int)color << 8U);
}

#endif // OS_VGA_H
