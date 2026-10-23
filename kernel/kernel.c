#include <stdlib.h>

#include <kernel/delay.h>
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
        char text[4];
        utoa(i, text, 10);
        tty_write_string(text);
        tty_put_char(' ');
        busy_wait(2000000);
    }

    for (int i = 0; i < 5; i++) {
        tty_scroll(1);
        tty_scroll(2);
        busy_wait(100000000);
    }
    tty_write_string("Scroll cursor move test");
    tty_write_string("\nNewline test 2");
}
