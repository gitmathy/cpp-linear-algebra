# Tests Makefile moved to repository root — builds two test executables
# - performance: main = tests/performance_test.cpp, built with -O3 -Ofast
# - unit:        main = tests/unit_tests.cpp, built with -g

CXX ?= g++-12

# Compiler flags (exactly as requested)
PERF_CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -O3 -Ofast -ffast-math -march=native -mtune=native -flto -mavx2 -fopt-info-vec-optimized -finline-limit=20000 -fstrict-aliasing -funroll-loops -floop-interchange -I. -MMD -MP -DPARALLEL
UNIT_CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -g -I. -MMD -MP

SRC_DIR := tests/src
PERF_TEST_DIR := $(SRC_DIR)/performance_tests
UNIT_TEST_DIR := $(SRC_DIR)/unit_tests
BUILD_DIR := builds
PERF_BUILD := $(BUILD_DIR)/perf
UNIT_BUILD := $(BUILD_DIR)/unit

PERF_MAIN := tests/performance_test.cpp
UNIT_MAIN := tests/unit_tests.cpp

# Source lists
COMMON_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
PERF_SRCS := $(wildcard $(PERF_TEST_DIR)/*.cpp)
UNIT_SRCS := $(wildcard $(UNIT_TEST_DIR)/*.cpp)

# Object files — separate directories so objects are compiled with different flags
# Map `tests/<path>.cpp` -> `tests/build/<perf|unit>/<path>.o` so pattern rules can use tests/%.cpp
PERF_OBJS := $(patsubst tests/%.cpp,$(PERF_BUILD)/%.o,$(COMMON_SRCS) $(PERF_SRCS) $(PERF_MAIN))
UNIT_OBJS := $(patsubst tests/%.cpp,$(UNIT_BUILD)/%.o,$(COMMON_SRCS) $(UNIT_SRCS) $(UNIT_MAIN))

PERF_TARGET := $(PERF_BUILD)/performance_test
UNIT_TARGET := $(UNIT_BUILD)/unit_tests

# Auto-generated dependency files (created by -MMD)
DEPS := $(PERF_OBJS:.o=.d) $(UNIT_OBJS:.o=.d)
-include $(DEPS)

.PHONY: all perf unit run-perf run-unit run-debug deps clean doxygen clean-doxygen

# Default: build both executables
all: perf unit

# Per-target shortcuts
perf: $(PERF_TARGET)
unit: $(UNIT_TARGET)

# Link rules - each executable links the objects compiled with the matching flags
$(PERF_TARGET): $(PERF_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(PERF_CXXFLAGS) -o $@ $^ -ltbb -flto

$(UNIT_TARGET): $(UNIT_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(UNIT_CXXFLAGS) -o $@ $^

# Debug binary for VS Code (builds/test) — compiles top-level test.cpp with unit flags
DEBUG_TARGET := $(BUILD_DIR)/test

debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): test.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(UNIT_CXXFLAGS) -o $@ $<

# Compilation rules (preserve source sub-path under tests/)
# target: tests/build/<perf|unit>/% .o -> source: tests/%.cpp
$(PERF_BUILD)/%.o: tests/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(PERF_CXXFLAGS) -c $< -o $@

$(UNIT_BUILD)/%.o: tests/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(UNIT_CXXFLAGS) -c $< -o $@

# Run targets
run-perf: $(PERF_TARGET)
	@echo "Running performance tests..."
	@$(PERF_TARGET)

run-unit: $(UNIT_TARGET)
	@echo "Running unit tests..."
	@$(UNIT_TARGET)

run-debug: $(DEBUG_TARGET)
	@echo "Running debug build..."
	@$(DEBUG_TARGET)

# Build dependency files (will compile object files and thereby generate .d files)
deps: $(DEPS)
	@echo "Dependencies updated"

# Clean everything
clean:
	rm -rf $(BUILD_DIR)

# Doxygen
doxygen:
	doxygen Doxyfile

clean-doxygen:
	rm -rf doxygen
