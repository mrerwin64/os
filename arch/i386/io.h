#ifndef OS_IO_H
#define OS_IO_H

#include <stdint.h>

static inline __attribute__((unused)) void outb(const uint16_t port, const uint8_t value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

static inline __attribute__((unused)) uint8_t inb(const uint16_t port) {
    uint8_t value;
    __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port) : "memory");
    return value;
}

#endif // OS_IO_H
