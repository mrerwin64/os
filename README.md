# os

A hobby operating system kernel for 32-bit x86, written from scratch in C and NASM assembly. It boots
through Multiboot (e.g. GRUB or QEMU's `-kernel`) and is an early-stage project I'm using to learn how
hardware and kernels work at the lowest level.

## What it does so far

- **Boot:** Multiboot header, sets up its own stack and jumps into C ([`arch/i386/boot.asm`](arch/i386/boot.asm))
- **GDT:** loads a flat segmentation model ([`arch/i386/gdt.c`](arch/i386/gdt.c), [`gdt_load.asm`](arch/i386/gdt_load.asm))
- **VGA text mode terminal:** 16 colors, line wrapping, scrolling, writing and coloring individual cells
  ([`arch/i386/tty.c`](arch/i386/tty.c))
- **`kprintf`:** formatted output with `%c %s %d %i %u %x %X %p` ([`kernel/kprintf.c`](kernel/kprintf.c))
- **Port I/O:** `inb`/`outb` wrappers ([`arch/i386/io.h`](arch/i386/io.h))
- **Minimal libc:** `strlen`, `atoi`, `itoa`, `utoa` with any base ([`libc/`](libc))
- **Boot screen:** the Peugeot lion emblem drawn in text mode, followed by a test sequence of scrolling text
  and an animated bouncing box

Architecture-specific code lives in `arch/i386/` behind small interfaces in `include/kernel/`, so the
generic kernel code doesn't depend on x86 details.

## Planned

Interrupts (IDT, PIC, keyboard), physical and virtual memory management, a heap.

## Building and running

Requirements: an `i686-elf` GCC cross-compiler (expected in `~/cross/bin`, override with `CROSS=`), NASM
and QEMU.

```bash
make            # builds build/os
make run        # boots it in QEMU
make debug      # boots it paused, waiting for GDB on port 1234
```

Code style is enforced with the included `.clang-format` and `.clang-tidy`.
