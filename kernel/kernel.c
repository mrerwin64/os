#include <kernel/logo.h>
#include <kernel/tty.h>
#include <stdlib.h>

void kernel_main(void)
{
	tty_init();

	tty_write_string("Hello, kernel World!\n");
	tty_write_string("Newline test\n");
	for (int i = 0; i < 1000; i++) {
		char text[12];
		itoa(i, text);
		tty_write_string(text);
		tty_put_char(' ');
		for (volatile unsigned long j = 0; j < 5000000; j++) {
			;
		}
	}
	logo_draw();
}
