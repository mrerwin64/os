#include <stdlib.h>

#include <stddef.h>

int atoi(const char* a) {
    size_t i = 0;
    int sign = 1;
    int result = 0;

    while (a[i] == ' ' || a[i] == '\t' || a[i] == '\n') {
        i++;
    }

    if (a[i] == '-' || a[i] == '+') {
        if (a[i] == '-') {
            sign = -1;
        }
        i++;
    }

    while (a[i] >= '0' && a[i] <= '9') {
        result = result * 10 + (a[i] - '0');
        i++;
    }

    return sign * result;
}

void utoa(unsigned int u, char* a, const unsigned int base) {
    static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    if (base < 2 || base > 36) {
        a[0] = '\0';
        return;
    }

    size_t length = 1;
    unsigned int copy = u / base;
    while (copy > 0) {
        length += 1;
        copy /= base;
    }

    a[length] = '\0';
    for (size_t j = length; j-- > 0;) {
        a[j] = digits[u % base];
        u /= base;
    }
}

void itoa(const int i, char* a, const unsigned int base) {
    unsigned int u = (unsigned int)i;
    if (i < 0) {
        a[0] = '-';
        a++;
        u = -u;
    }

    utoa(u, a, base);
}
