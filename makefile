.RECIPEPREFIX = >

CC := i686-elf-gcc
AR := i686-elf-ar
AS := nasm

BUILD := $(CURDIR)/build
KERNEL := $(CURDIR)/kernel
LIBC := $(CURDIR)/libc

ASFLAGS := -felf32
CFLAGS := -I$(LIBC)/ -I$(KERNEL)/ -O2 -std=c99 -ffreestanding -T linker.ld
LIBS := -L$(BUILD)/ -lgcc -lk -nostdlib

CWARNINGS := -Wall -Wextra -Werror=shadow -Wswitch-enum -pedantic
CNOWARNINGS := -Wno-strict-prototypes

export

.PHONY: default
default: mkdir build/kernel

.PHONY: build/kernel
build/kernel: build/libk.a
> $(MAKE) -C kernel/arch/i386

.PHONY: build/libk.a
build/libk.a:
> $(MAKE) -C libc

.PHONY: grub-iso
grub-iso: build/kernel
> mkdir -p build/iso
> mkdir -p build/iso/boot
> mkdir -p build/iso/boot/grub
>
> cp build/kernel build/iso/boot/kernel
> cp grub.cfg     build/iso/boot/grub/grub.cfg
>
> grub-mkrescue -o build/lake.iso build/iso

.PHONY: qemu
qemu: default
> qemu-system-i386 -kernel build/kernel

.PHONY: mkdir
mkdir:
> mkdir -p build

.PHONY: clean
clean:
> rm -rf build/

