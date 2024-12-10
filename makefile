.RECIPEPREFIX = >

CC := i686-elf-gcc
AR := i686-elf-ar
AS := nasm

BUILD := build
KERNEL := kernel
LIBC := libc

ASFLAGS := -felf32
CFLAGS := -I$(LIBC)/ -I$(KERNEL)/ -O2 -std=gnu99 -ffreestanding
LIBS := -L$(BUILD)/ -lgcc -lk -nostdlib -T kernel/arch/i386/linker.ld

LAKE_CSOURCES := $(wildcard $(KERNEL)/arch/i386/*.c) \
				 $(wildcard $(KERNEL)/*.c)
LAKE_COBJECTS := $(patsubst %.c, $(BUILD)/%.o, $(LAKE_CSOURCES))

LAKE_ASMSOURCES := $(wildcard $(KERNEL)/arch/i386/*.asm)
LAKE_ASMOBJECTS := $(patsubst %.asm, $(BUILD)/%.o, $(LAKE_ASMSOURCES))

LAKE_OBJECTS := $(LAKE_COBJECTS) $(LAKE_ASMOBJECTS)

LIBC_CSOURCES := $(wildcard $(LIBC)/*.c)
LIBC_COBJECTS := $(patsubst %.c, $(BUILD)/%.o, $(LIBC_CSOURCES))

LIBC_OBJECTS := $(LIBC_COBJECTS)

CWARNINGS := -Wall -Wextra -Werror=vla -Werror=shadow -Wswitch-enum -pedantic
CNOWARNINGS := -Wno-strict-prototypes

export

.PHONY: default
default: mkdir $(BUILD)/lake

$(BUILD)/lake: $(LAKE_OBJECTS) $(BUILD)/libk.a
> @mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(LAKE_OBJECTS) $(LIBS)
> grub-file --is-x86-multiboot $(BUILD)/lake

$(BUILD)/libk.a: $(LIBC_OBJECTS)
> @mkdir -p $(dir $@)
> $(AR) rcs $@ $(LIBC_OBJECTS)

$(BUILD)/%.o: %.c $(DEPS)
> @mkdir -p $(dir $@)
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o $@ $<

$(BUILD)/%.o: %.asm
> @mkdir -p $(dir $@)
> $(AS) $(ASFLAGS) -o $@ $<

.PHONY: grub-iso
grub-iso: $(BUILD)/lake
> mkdir -p $(BUILD)/iso/boot/grub
>
> cp $(BUILD)/lake $(BUILD)/iso/boot/lake
> cp grub.cfg      $(BUILD)/iso/boot/grub/grub.cfg
>
> grub-mkrescue -o $(BUILD)/lake.iso $(BUILD)/iso

.PHONY: qemu
qemu: default
> qemu-system-i386 -kernel $(BUILD)/lake

.PHONY: qemu-dint
qemu-dint: default
> qemu-system-i386 -kernel $(BUILD)/lake -d int --no-reboot

.PHONY: mkdir
mkdir:
> mkdir -p build

.PHONY: clean
clean:
> rm -rf build/

