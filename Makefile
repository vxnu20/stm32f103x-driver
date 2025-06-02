# Compiler and tools
CC       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy
SIZE     = arm-none-eabi-size

# Target name
TARGET   = image

# Directories
SRC_DIR     = src
INC_DIR     = include
BUILD_DIR   = build

# Files
SOURCES     = $(wildcard $(SRC_DIR)/*.c)
OBJECTS     = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
LINKER_SCRIPT = linker.ld

# Flags
CFLAGS      = -mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -g -I$(INC_DIR)
LDFLAGS     = -T $(LINKER_SCRIPT)

# Default target
all: $(BUILD_DIR)/$(TARGET).elf

# Build ELF
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

# Create build directory if needed
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile .c to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Flash target
flash: all
	openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg \
		-c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

# Clean up
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean flash