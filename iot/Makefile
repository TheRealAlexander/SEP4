MCU = atmega2560
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
LDFLAGS = -mmcu=$(MCU)

SRC_DIR = src
TEST_SRC_DIR = tests
BUILD_DIR = build

# Find source files, convert to object file paths
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

# For tests
TEST_FILES = $(shell find $(TEST_SRC_DIR) -name '*.c')
TEST_OBJ_FILES = $(TEST_FILES:%.c=$(BUILD_DIR)/%.o)
TEST_EXEC = test_exec

all: build

build: $(OBJ_FILES)
    $(CC) $(LDFLAGS) $^ -o $(BUILD_DIR)/main.elf
    $(OBJCOPY) -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

$(BUILD_DIR)/%.o: %.c
    @mkdir -p $(@D)
    $(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ_FILES)
    $(CC) $(LDFLAGS) $(TEST_OBJ_FILES) -o $(BUILD_DIR)/$(TEST_EXEC)
    ./$(BUILD_DIR)/$(TEST_EXEC)

clean:
    rm -rf $(BUILD_DIR)

.PHONY: all build test clean
