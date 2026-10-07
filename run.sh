#!/bin/sh
# Build the kernel, then boot it in QEMU. Extra arguments are passed to QEMU.
set -eu
cd "$(dirname "$0")"

./build.sh

set -x
qemu-system-i386 -kernel os "$@"
