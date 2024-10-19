.RECIPEPREFIX = >

CC := i686-elf-gcc1
AS := nasm

CFLAGS := -O2 -std=c99 -ffreestanding -T linker.ld -nostdlib
LIBS := -lgcc

ASFLAGS := -felf32

CWARNINGS := -Wall -Wextra -Werror=shadow -Wswitch-enum -pedantic
CNOWARNINGS := -Wno-strict-prototypes

SOURCES := kernel.c vga.c string.c
ASMSOURCES := boot.asm

kernel: kernel.o boot.o
> $(CC) $(CFLAGS) -o kernel kernel.o boot.o $(LIBS)

kernel.o: $(SOURCES)
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o kernel.o $(SOURCES)

boot.o: boot.asm
> $(AS) $(ASFLAGS) -o boot.o boot.asm

.PHONY: clean
clean:
> rm -rf build

