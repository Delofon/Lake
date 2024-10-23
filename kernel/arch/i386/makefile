.RECIPEPREFIX = >

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(BUILD)/%.o, $(SOURCES))

ASMSOURCES := $(wildcard *.asm)
ASMOBJECTS := $(patsubst %.asm, $(BUILD)/%.o, $(ASMSOURCES))

.PHONY: default
default: $(BUILD)/kernel

.PHONY: $(BUILD)/libk.a
$(BUILD)/kernel: $(OBJECTS) $(ASMOBJECTS) $(BUILD)/libk.a
> $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
> grub-file --is-x86-multiboot $(BUILD)/kernel

$(BUILD)/%.o: %.c
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o $@ $<

$(BUILD)/%.o: %.asm
> $(AS) $(ASFLAGS) -o $@ $<

