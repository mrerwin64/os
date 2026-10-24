#include "gdt.h"

#include <stdint.h>

struct gdt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void gdt_load(const struct gdt_pointer* pointer);

void gdt_init(void) {
    static uint64_t table[3] = {0, 0x00CF9A000000FFFF, 0x00CF92000000FFFF};

    struct gdt_pointer pointer = {
        .limit = sizeof(table) - 1,
        .base = (uint32_t)table,
    };

    gdt_load(&pointer);
}
