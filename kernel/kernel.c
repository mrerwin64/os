#include <stddef.h>
#include <stdint.h>

#include <kernel/delay.h>
#include <kernel/kprintf.h>
#include <kernel/logo.h>
#include <kernel/tty.h>

// ReSharper disable once CppUseInternalLinkage
void kernel_main(void) { // NOLINT(*-use-internal-linkage)
    tty_init();

    logo_draw(1000000);
    busy_wait(1000000000);

    tty_write_string("Hello, kernel World!\n");
    tty_write_string("Newline test\n");
    for (unsigned int i = 0; i < 1000; i++) {
        kprintf("%u ", i);
        busy_wait(2000000);
    }

    for (int i = 0; i < 5; i++) {
        tty_scroll(1);
        tty_scroll(2);
        busy_wait(100000000);
    }
    tty_write_string("Scroll cursor move test");
    tty_write_string("\nNewline test 2");

    busy_wait(999999999);
    const size_t width = tty_width();
    const size_t height = tty_height();
    int box_x = 1;
    int box_y = 1;
    int move_x = -1;
    int move_y = -1;
    unsigned int i = 0;
    static const uint8_t box_colors[] = {
        TTY_COLOR_LIGHT_BLUE,
        TTY_COLOR_LIGHT_MAGENTA,
        TTY_COLOR_LIGHT_GREEN,
        TTY_COLOR_LIGHT_RED,
    };
    while (i < (unsigned int)-1) {
        // Remove the current box
        tty_set_color_at(tty_get_color(), box_x, box_y);
        tty_set_color_at(tty_get_color(), box_x + 1, box_y);
        tty_set_color_at(tty_get_color(), box_x, box_y + 1);
        tty_set_color_at(tty_get_color(), box_x + 1, box_y + 1);

        // Move the box cursor
        if (box_x == 0 || (size_t)box_x == width - 2) {
            move_x *= -1;
        }
        box_x += move_x;
        if (box_y == 0 || (size_t)box_y == height - 2) {
            move_y *= -1;
        }
        box_y += move_y;

        kprintf("\n%u %u", i, i * i * i);

        // Draw the new box
        tty_set_bg_at(box_colors[i % 4], box_x, box_y);
        tty_set_bg_at(box_colors[(i + 1) % 4], box_x + 1, box_y);
        tty_set_bg_at(box_colors[(i + 3) % 4], box_x, box_y + 1);
        tty_set_bg_at(box_colors[(i + 2) % 4], box_x + 1, box_y + 1);

        busy_wait(i * i * i);
        i++;
    }
}
