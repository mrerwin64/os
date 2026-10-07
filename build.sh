#!/bin/sh
# Run all three steps, then check the Multiboot header
set -eu
cd "$(dirname "$0")"

./assemble.sh
./compile.sh
./link.sh

if command -v grub2-file >/dev/null 2>&1; then
	if grub2-file --is-x86-multiboot os; then
		echo "multiboot header OK"
	else
		echo "multiboot header NOT found" >&2
		exit 1
	fi
fi
