#include <stddef.h>
#include <stdlib.h>

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

void itoa(const int i, char* a) {
    unsigned int u = i;
    if (i < 0) {
        a[0] = '-';
        a++;
        u = -u;
    }

    size_t length = 1;
    unsigned int copy = u / 10;
    while (copy > 0) {
        length += 1;
        copy /= 10;
    }

    a[length] = '\0';
    for (size_t j = length; j-- > 0; ) {
        a[j] = (char)(u % 10 + '0');
        u /= 10;
    }
}
