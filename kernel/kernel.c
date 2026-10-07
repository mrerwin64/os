#include <kernel/tty.h>

void kernel_main(void)
{
	tty_init();

	tty_write_string("Hello, kernel World!\n");
	tty_write_string("Newline test\n");
}
