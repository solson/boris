# Output executable name
OUTPUT := boris

# Compiler options
CC := clang
override CFLAGS += -MMD -Iinclude -Wall -Wextra

# Find all sources
SOURCES := $(shell find src/ -name '*.c')
OBJECTS := $(SOURCES:%.c=%.o)
DFILES  := $(SOURCES:%.c=%.d)

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Dependency files from -MMD
-include $(DFILES)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(DFILES) $(OUTPUT)

.PHONY: all clean
