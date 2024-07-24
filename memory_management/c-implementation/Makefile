CXX = gcc
CXXFLAGS = -Wall -Wextra -g
INCLUDES = -I include
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin

# Source files
SOURCES = $(SRC_PATH)/Main.c $(SRC_PATH)/MemoryManager.c

# Object files
OBJECTS = $(patsubst $(SRC_PATH)/%.c,$(BUILD_PATH)/%.o,$(SOURCES))

# Executable
BIN_NAME = memory_manager

.PHONY: all clean dirs

all: $(BIN_PATH)/$(BIN_NAME)

$(BIN_PATH)/$(BIN_NAME): $(OBJECTS) | dirs
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c | dirs
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

dirs:
	@echo "Creating directories"
	@mkdir -p $(BUILD_PATH) $(BIN_PATH)

clean:
	@echo "Cleaning up"
	@rm -rf $(BUILD_PATH)

