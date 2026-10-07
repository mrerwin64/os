#ifndef OS_VGA_H
#define OS_VGA_H

#include <stdint.h>

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

static inline uint8_t vga_entry_color(const uint8_t fg, const uint8_t bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(const unsigned char uc, const uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

#endif //OS_VGA_H
