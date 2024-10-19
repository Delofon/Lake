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

kernel: $(OBJECTS) $(ASMOBJECTS)
> $(CC) $(CFLAGS) -o build/kernel $^ $(LIBS)

%.o: %.c mkdir
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o build/$@ $<

%.o: %.asm mkdir
> $(AS) $(ASFLAGS) -o build/$@ $<

.PHONY: mkdir
mkdir:
> mkdir -p build

.PHONY: clean
clean:
> rm -rf build/

