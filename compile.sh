#!/bin/sh
# Compile kernel.c -> kernel.o
set -eu
PATH="$HOME/cross/bin:$PATH"
cd "$(dirname "$0")"

set -x
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
