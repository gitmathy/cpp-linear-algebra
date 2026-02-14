# Tests Makefile — builds performance/src/*.cpp into performance/build/test

CXX := g++-12
CXXFLAGS := -Wall -Wextra -pedantic -std=c++23 -g -I.. -I.
SRC_DIR := src
BUILD_DIR := build
# Include test runner (test.cpp) plus all sources under src/
SOURCES := test.cpp $(wildcard $(SRC_DIR)/*.cpp)
# Map any .cpp -> build/<same-path>.o (preserves directory structure)
OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET := $(BUILD_DIR)/test

.PHONY: all clean run format

all: $(TARGET)

# Link
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile (preserve source filename under build/). Matches both test.cpp and src/*.cpp
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the test executable
run: $(TARGET)
	@echo "Running tests..."
	@$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Format test sources (if clang-format is available)
format:
	clang-format -i $(SOURCES) ../test.cpp ../includes/*.h || true
