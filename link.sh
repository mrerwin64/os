#!/bin/sh
# Link boot.o + kernel.o -> os, using linker.ld
set -eu
PATH="$HOME/cross/bin:$PATH"
cd "$(dirname "$0")"

set -x
i686-elf-gcc -T linker.ld -o os -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
