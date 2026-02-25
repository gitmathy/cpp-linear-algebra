CXX ?= g++-12

# Performance compiler flags from the root Makefile.
# You may need to adjust the include path for Eigen depending on your system.
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -O3 -Ofast -ffast-math -march=native -mtune=native -flto -mavx2 -fopt-info-vec-optimized -finline-limit=20000 -fstrict-aliasing -funroll-loops -floop-interchange -MMD -MP -DPARALLEL -I/usr/include/eigen3 -I../

TARGET := eigen_main.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): main.cpp ../tests/src/timing.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp ../tests/src/timing.cpp

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) *.d
