.RECIPEPREFIX = >

CC := i686-elf-gcc
AR := i686-elf-ar
AS := nasm

BUILD := build
KERNEL := kernel
LIBC := libc
EXT := external

LDS := kernel/arch/i386/boot/linker.ld

INCLUDE_DIRS := -I$(LIBC)/ \
				-I$(KERNEL)/ \
				-I$(EXT)/include/ \

ASFLAGS := -felf32 -g
#CFLAGS := $(INCLUDE_DIRS) -O2 -std=gnu99 -ffreestanding -MMD -MP
CFLAGS := $(INCLUDE_DIRS) -Og -ggdb -std=gnu99 -ffreestanding -MMD -MP
LIBS := -L$(BUILD)/ -lgcc -lk -nostdlib -T $(LDS)

LAKE_CSOURCES := $(wildcard $(KERNEL)/arch/i386/*.c) \
                 $(wildcard $(KERNEL)/arch/i386/boot/*.c) \
				 $(wildcard $(KERNEL)/drv/*.c) \
				 $(wildcard $(KERNEL)/*.c)
LAKE_COBJECTS := $(patsubst %, $(BUILD)/%.o, $(LAKE_CSOURCES))

LAKE_ASMSOURCES := $(wildcard $(KERNEL)/arch/i386/*.asm) \
                   $(wildcard $(KERNEL)/arch/i386/boot/*.asm)
LAKE_ASMOBJECTS := $(patsubst %, $(BUILD)/%.o, $(LAKE_ASMSOURCES))

LAKE_OBJECTS := $(LAKE_COBJECTS) $(LAKE_ASMOBJECTS)

LIBC_CSOURCES := $(wildcard $(LIBC)/*.c)
LIBC_COBJECTS := $(patsubst %, $(BUILD)/%.o, $(LIBC_CSOURCES))

LIBC_OBJECTS := $(LIBC_COBJECTS)

DEPS := $(patsubst %, $(BUILD)/%.d, $(LAKE_CSOURCES)) \
		$(patsubst %, $(BUILD)/%.d, $(LIBC_CSOURCES)) \
		$(patsubst %, $(BUILD)/%.d, $(LAKE_ASMOBJECTS))

CWARNINGS := -Wall -Wextra -Werror=vla -Werror=shadow -Wswitch-enum \
             -Wno-strict-prototypes

.PHONY: default
default: $(BUILD)/lake

-include $(DEPS)

$(BUILD)/lake: $(LAKE_OBJECTS) $(BUILD)/libk.a makefile $(LDS)
> @mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -o $@ $(LAKE_OBJECTS) $(LIBS)
> grub-file --is-x86-multiboot $(BUILD)/lake

$(BUILD)/libk.a: $(LIBC_OBJECTS)
> @mkdir -p $(dir $@)
> $(AR) rcs $@ $(LIBC_OBJECTS)

$(BUILD)/%.c.o: %.c makefile
> @mkdir -p $(dir $@)
> $(CC) $(CFLAGS) $(CWARNINGS) -c -o $@ $<

$(BUILD)/%.asm.o: %.asm makefile
> @mkdir -p $(dir $@)
> $(AS) $(ASFLAGS) -MD -MP -o $@ $<

$(EXT)/include/multiboot.h:
> @mkdir -p $(dir $@)
> curl --output-dir $(dir $@) -OL https://cgit.git.savannah.gnu.org/cgit/grub.git/plain/doc/multiboot.h?h=multiboot

$(EXT)/include/multiboot2.h:
> @mkdir -p $(dir $@)
> curl --output-dir $(dir $@) -OL https://cgit.git.savannah.gnu.org/cgit/grub.git/plain/doc/multiboot2.h?h=multiboot2

.PHONY: download-mb-hdr
download-mb-hdr: $(EXT)/include/multiboot.h $(EXT)/include/multiboot2.h

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

.PHONY: gdb
gdb: default
> qemu-system-i386 -s -S -kernel $(BUILD)/lake

.PHONY: qemu-dint
qemu-dint: default
> qemu-system-i386 -kernel $(BUILD)/lake -d int --no-reboot

.PHONY: qemu-log
qemu-log: default
> qemu-system-i386 -kernel $(BUILD)/lake -d int,cpu_reset --no-reboot

.PHONY: clean
clean:
> rm -rf $(BUILD)/
> rm -rf $(EXT)/

