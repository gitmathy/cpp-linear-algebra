# Compiler and flags
CXX := g++-12
#CXXFLAGS := -Wall -Wextra -pedantic -std=c++23 -O3 -Ofast -I.
CXXFLAGS := -Wall -Wextra -pedantic -std=c++23 -g -I.
LDFLAGS :=

# Directories
SRC_DIR := src
INC_DIR := includes
BUILD_DIR := builds

# Find all .cpp files under $(SRC_DIR) (recursive) and include top-level main.cpp if present
SOURCES := $(shell test -f main.cpp && echo main.cpp || true) $(shell find $(SRC_DIR) -name '*.cpp' 2>/dev/null)

# Map source files to object files inside $(BUILD_DIR)
OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# If no sources found, warn and stop early
ifeq ($(strip $(SOURCES)),)
$(error No source files found in $(SRC_DIR) and no top-level main.cpp present)
endif
TARGET := test
TARGET_PATH := $(BUILD_DIR)/$(TARGET)

# Default target
all: $(TARGET_PATH)

# Build executable placed in $(BUILD_DIR)
$(TARGET_PATH): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files under $(BUILD_DIR), preserving directory structure
# Example: src/foo/bar.cpp -> builds/src/foo/bar.o
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Convenience target to build the named target (keeps backward compatibility)
$(TARGET):
	@$(MAKE) $(TARGET_PATH)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Format all C++ files (recursive)
format:
	clang-format -i $(shell find $(SRC_DIR) -name '*.cpp' -or -name '*.cc' 2>/dev/null) \
		$(shell find $(INC_DIR) -name '*.h' -or -name '*.hpp' 2>/dev/null)

# Phony targets
.PHONY: all clean format help $(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all    - Build the $(TARGET) executable (default -> $(TARGET_PATH))"
	@echo "  clean  - Remove the $(BUILD_DIR) directory"
	@echo "  format - Format all C++ source and header files under $(SRC_DIR) / $(INC_DIR)"
	@echo "  help   - Show this help message"
