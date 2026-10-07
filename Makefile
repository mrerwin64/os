CROSS		?= $(HOME)/cross/bin/i686-elf-
CC			:= $(CROSS)gcc
AS			:= $(CROSS)as

ARCH		?= i386
ARCHDIR		:= arch/$(ARCH)

BUILDDIR	:= build
OBJDIR		:= $(BUILDDIR)/object
KERNELBIN	:= $(BUILDDIR)/os

CFLAGS		:= -std=gnu99 -ffreestanding -O2 -g -Wall -Wextra -Wstrict-prototypes -Wold-style-definition -Iinclude

LDFLAGS		:= -T $(ARCHDIR)/linker.ld -ffreestanding -O2 -nostdlib
LIBS		:= -lgcc

ASM_SRCS	:= $(wildcard $(ARCHDIR)/*.s)
C_SRCS		:= $(wildcard $(ARCHDIR)/*.c kernel/*.c libc/*.c)

OBJS		:= $(ASM_SRCS:%.s=$(OBJDIR)/%.o) $(C_SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all run debug clean

all: $(KERNELBIN)

$(KERNELBIN): $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $< -o $@

run: $(KERNELBIN)
	qemu-system-i386 -kernel $< $(QEMUFLAGS)

debug: $(KERNELBIN)
	qemu-system-i386 -kernel $< -s -S $(QEMUFLAGS)

clean:
	rm -rf $(BUILDDIR)

-include $(OBJS:.o=.d)
