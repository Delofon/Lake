.RECIPEPREFIX = >

CC := i686-elf-gcc
AS := nasm

BUILD := ../../../build
LIBC := ../../../libc

CFLAGS := -I$(LIBC)/ -O2 -std=c99 -ffreestanding -T linker.ld -nostdlib
LIBS := -L$(BUILD)/ -lgcc -lk

ASFLAGS := -felf32

CWARNINGS := -Wall -Wextra -Werror=shadow -Wswitch-enum -pedantic
CNOWARNINGS := -Wno-strict-prototypes

SOURCES := $(wildcard *.c) ../../kernel.c
OBJECTS := $(patsubst %.c, $(BUILD)/%.o, $(SOURCES))

ASMSOURCES := $(wildcard *.asm)
ASMOBJECTS := $(patsubst %.asm, $(BUILD)/%.o, $(ASMSOURCES))

.PHONY: default
default: $(BUILD)/kernel

$(BUILD)/kernel: $(OBJECTS) $(ASMOBJECTS)
> $(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD)/%.o: %.c
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o $@ $<

$(BUILD)/%.o: %.asm
> $(AS) $(ASFLAGS) -o $@ $<

