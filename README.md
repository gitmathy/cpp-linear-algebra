# cpp-linear-algebra

![Makefile CI](https://github.com/gitmathy/cpp-linear-algebra/actions/workflows/cpp-build.yaml/badge.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue.svg)

A modern C++20 library for high-performance linear algebra.

`cpp-linear-algebra` is a header-only library that provides efficient matrix and vector operations. It leverages template expressions to avoid unnecessary temporary objects and can be accelerated with Intel's Threading Building Blocks (TBB).

## Features

*   **Matrix and Vector classes:** Easy-to-use, generic `la::matrix` and `la::vector` classes.
*   **Template Expressions:** Operations like addition, subtraction, and multiplication are implemented using expression templates, which result in highly optimized, loop-fused code at compile time.
*   **Flexible Storage:** Matrices can be configured for row-wise or column-wise storage for optimal performance in different scenarios.
*   **Parallel Execution:** Can be accelerated using Intel TBB for parallel execution of expensive operations.
*   **Algorithms:** Includes common linear algebra algorithms, such as LU decomposition for solving systems of linear equations.
*   **Header-Only Option:** Can be used as a simple header-only library if no performance acceleration is needed.

## Requirements

*   **C++20** compatible compiler (e.g., GCC 12+, Clang 14+, MSVC v19.29+).
*   **CMake** (version 3.22 or newer).
*   **Git**.
*   (Optional) **Intel Threading Building Blocks (TBB)** for parallel execution support.

## Building the Project

The project uses CMake to build tests and examples.

### Debug Build (for development and running unit tests)

```bash
mkdir build-debug
cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

You can then run the unit tests and a debug executable:
```bash
./unit/unit_tests
./debug/debug_test
```

### Release Build (for performance testing)

For performance-critical builds, use the Release configuration. This enables optimizations and parallel execution (if TBB is found).

```bash
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

You can then run the performance benchmarks:
```bash
./perf/performance_test
```

## Usage

Here is a quick example of how to use the library to perform basic vector and matrix operations.

```cpp
#include <iostream>
#include "la.hpp"
#include "matrix.hpp"
#include "vector.hpp"

int main() {
    // Create two vectors
    la::vector<double> v1 = {1.0, 2.0, 3.0};
    la::vector<double> v2(3, 4.0); // A vector of size 3 with all elements as 4.0

    // Add them together using expression templates
    la::vector<double> v_sum = v1 + v2;
    std::cout << "v1 + v2 = \n" << v_sum << std::endl;

    // Create a 2x3 matrix
    la::matrix<double> m1 = {{1, 2, 3}, {4, 5, 6}};

    // Create another 2x3 matrix
    la::matrix<double> m2(2, 3, 10.0);

    // Subtract m2 from m1
    la::matrix<double> m_diff = m1 - m2;
    std::cout << "m1 - m2 = \n" << m_diff << std::endl;

    // Compute the L2 norm of a vector
    double norm_v1 = la::norm(v1);
    std::cout << "Norm of v1 = " << norm_v1 << std::endl;

    return 0;
}
```

## Contributing

Contributions are welcome! If you'd like to help, you can start by looking for areas to improve.

*   **Implement New Algorithms:** We are always looking to expand the library's features.
*   **Improve Documentation:** Enhancing the documentation helps everyone.
*   **Add More Tests:** Increasing test coverage makes the library more robust.
*   **Fix Known Issues:** See the issues of this repository.

### Coding Style

When contributing, please try to match the existing coding style. The project uses `.clang-format` to enforce a consistent style, so please apply it to your changes. While `.clang-format` enforces much of the style, here are some additional guidelines to follow:

*   **line length:** 80
*   **case:** `snake_case`, except template parameters in `PascalCase`.
*   **trailing whitespaces:** Not allowed.
*   **comments:** Use `//` for general comments and `///` for Doxygen documentation. Avoid `/* */`. Public functions should have at least a brief description.
*   **Curly braces:** Opening braces go on the same line for functions and control structures, but on a new line for classes and structs. All blocks should be enclosed by curly braces.
*   **file suffixes:** Use `.hpp` for header files and `.cpp` for implementation files.
*   **variable prefixes:** Member variables should be prefixed with `p_` (e.g., `p_rows`).
*   **class and struct:** Use `struct` only for plain old data (POD) types with all public members.
*   **nullpointer:** Always use `nullptr` instead of `0`.

## Documentation

This project uses Doxygen for generating API documentation. To build the documentation, you need to have Doxygen installed.

You can generate the documentation by running:

```bash
doxygen Doxyfile
```

The output will be in the `doxygen/` directory.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
