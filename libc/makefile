.RECIPEPREFIX = >

CC := i686-elf-gcc
AR := i686-elf-ar

BUILD := ../build

CFLAGS := -O2 -std=c99 -ffreestanding

CWARNINGS := -Wall -Wextra -Werror=shadow -Wswitch-enum -pedantic
CNOWARNINGS := -Wno-strict-prototypes

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(BUILD)/%.o, $(SOURCES))

.PHONY: default
default: $(BUILD)/libk.a

$(BUILD)/libk.a: $(OBJECTS)
> $(AR) rcs $@ $(OBJECTS)

$(BUILD)/%.o: %.c
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o $@ $<

