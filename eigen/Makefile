CXX ?= g++-12

# Performance compiler flags from the root Makefile.
# You may need to adjust the include path for Eigen depending on your system.
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20  -Ofast -march=native -flto -fstrict-aliasing -fopt-info-vec-optimized -I. -MMD -MP -DPARALLEL -I/usr/include/eigen3 -I../

TARGET := eigen_main.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): main.cpp ../tests/src/timing.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp ../tests/src/timing.cpp

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) *.d
