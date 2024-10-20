.RECIPEPREFIX = >

CC := i686-elf-gcc
AS := nasm

CFLAGS := -O2 -std=c99 -ffreestanding -T linker.ld -nostdlib
LIBS := -lgcc

ASFLAGS := -felf32

CWARNINGS := -Wall -Wextra -Werror=shadow -Wswitch-enum -pedantic
CNOWARNINGS := -Wno-strict-prototypes

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, build/%.o, $(SOURCES))

ASMSOURCES := $(wildcard *.asm)
ASMOBJECTS := $(patsubst %.asm, build/%.o, $(ASMSOURCES))

.PHONY: default
default: mkdir build/kernel

build/kernel: $(OBJECTS) $(ASMOBJECTS)
> $(CC) $(CFLAGS) -o $@ $^ $(LIBS)

build/%.o: %.c
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o $@ $<

build/%.o: %.asm
> $(AS) $(ASFLAGS) -o $@ $<

.PHONY: grub-iso
grub-iso: build/kernel
> grub-file --is-x86-multiboot build/kernel
>
> mkdir -p build/iso
> mkdir -p build/iso/boot
> mkdir -p build/iso/boot/grub
>
> cp build/kernel build/iso/boot/kernel
> cp grub.cfg     build/iso/boot/grub/grub.cfg
>
> grub-mkrescue -o build/lake.iso build/iso

.PHONY: mkdir
mkdir:
> mkdir -p build

.PHONY: clean
clean:
> rm -rf build/

