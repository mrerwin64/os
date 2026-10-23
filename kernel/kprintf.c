#include <kernel/kprintf.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <kernel/tty.h>

void kprintf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    size_t i = 0;
    while (format[i]) {
        if (format[i] == '%' && format[i + 1]) {
            const char type = format[i + 1];
            switch (type) {
                case '%': tty_put_char('%'); break;
                case 'c': tty_put_char((char)va_arg(args, int)); break;
                case 's': {
                    const char* s = va_arg(args, char*);
                    tty_write_string(s ? s : "(null)");
                    break;
                }
                case 'd':
                case 'i': {
                    char text[12];
                    itoa(va_arg(args, int), text, 10);
                    tty_write_string(text);
                    break;
                }
                case 'u': {
                    char text[11];
                    utoa(va_arg(args, unsigned int), text, 10);
                    tty_write_string(text);
                    break;
                }
                case 'X':
                case 'x': {
                    char text[9];
                    utoa(va_arg(args, unsigned int), text, 16);
                    tty_write_string(text);
                    break;
                }
                case 'p': {
                    char text[11] = "0x";
                    utoa((uintptr_t)va_arg(args, void*), text + 2, 16);
                    tty_write_string(text);
                    break;
                }
                default:
                    tty_put_char('%');
                    tty_put_char(type);
                    break;
            }
            i++;
        }
        else {
            tty_put_char(format[i]);
        }
        i++;
    }

    va_end(args);
}
