# Compiler and tools
CC 		= arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE	= arm-none-eabi-size

TARGET = firmware

# Directories
SRC_DIR		= src
INC_DIR		= include
BUILD_DIR	= build

# Linker script
LINKER_SCRIPT = linker.ld

# Compiler flags
CFLAGS = -mcpu=cortex-m3 \
         -mthumb \
         -Wall \
         -Wextra \
         -std=c99 \
         -O2 \
         -g \
         -I$(INC_DIR)

# Linker flags
LDFLAGS = -T$(LINKER_SCRIPT) \
          -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

#Find all C source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Default target
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create ELF
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

# Create binary file from ELF
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Debug target - compile with debug symbols and no optimization
debug: CFLAGS += -DDEBUG -O0
debug: all

# Declare phony targets
.PHONY: all clean debug