.RECIPEPREFIX = >

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(BUILD)/%.o, $(SOURCES))

.PHONY: default
default: $(BUILD)/libk.a

$(BUILD)/libk.a: $(OBJECTS)
> $(AR) rcs $@ $(OBJECTS)

$(BUILD)/%.o: %.c
> $(CC) $(CFLAGS) $(CWARNINGS) $(CNOWARNINGS) -c -o $@ $<

