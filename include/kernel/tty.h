#ifndef OS_TTY_H
#define OS_TTY_H

#include <stdint.h>
#include <stddef.h>

enum tty_color {
    TTY_COLOR_BLACK = 0,
    TTY_COLOR_BLUE = 1,
    TTY_COLOR_GREEN = 2,
    TTY_COLOR_CYAN = 3,
    TTY_COLOR_RED = 4,
    TTY_COLOR_MAGENTA = 5,
    TTY_COLOR_BROWN = 6,
    TTY_COLOR_LIGHT_GREY = 7,
    TTY_COLOR_DARK_GREY = 8,
    TTY_COLOR_LIGHT_BLUE = 9,
    TTY_COLOR_LIGHT_GREEN = 10,
    TTY_COLOR_LIGHT_CYAN = 11,
    TTY_COLOR_LIGHT_RED = 12,
    TTY_COLOR_LIGHT_MAGENTA = 13,
    TTY_COLOR_LIGHT_BROWN = 14,
    TTY_COLOR_WHITE = 15,
};

void tty_init(void);
void tty_put_char_at(char c, uint8_t color, size_t x, size_t y);
void tty_put_char(char c);
void tty_write(const char* data, size_t size);
void tty_write_string(const char* data);

#endif //OS_TTY_H
