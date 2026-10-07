#!/bin/sh
# Assemble boot.s -> boot.o
set -eu
PATH="$HOME/cross/bin:$PATH"
cd "$(dirname "$0")"

set -x
i686-elf-as boot.s -o boot.o
