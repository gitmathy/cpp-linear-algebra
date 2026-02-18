# cpp-linear-algebra

This project provides efficient matrix and vector operations for C++. It is written in plain C++. It can be used without any library, i.e., just header files.

## How to use

Copy the files and directory from [./includes/](./includes/) to your setup and make sure the compiler finds those headers, i.e., set `-I<PATH>`. As of now, the following g++ compiler options are recommended: `-std=c++20 -O3 -Ofast -DPARALLEL`.

## Features

* Plain C++, solely using STL and C++. No need for other libraries
* Providing `vector` and `matrix` with basic linear algebra operations.
* OKish test coverage.


### Computing norms of vectors and matrices

```cpp
#include "includes/la.hpp"

la::vector<double> v(2);
double norm_2 = la::norm(v);    // Same as la::norm<2>(v)
double norm_1 = la::norm<1>(v);
double norm_max = la::norm<UINT_MAX>(v);
```

## Contributing

TODO

## Coding style

For this project we try hard to follow this formatting rules. Some of them are enforced by the format definition file, see [.clang-format](.clang-format).

| Format Parameter     | Style                                                      |
|----------------------|------------------------------------------------------------|
| line length          | 80                                                         |
| case                 | snake case, except template parameters in PascalCase       |
| trailing whitespaces | not allowed                                                |
| comments             | `//` or `///` for Doxygen comments, avoid `/* */`          |
|                      | For public functions provide at least a brief description  |
| Curly braces         | Opens on same line, except for classes                     |
|                      | All blocks should be enclosed by curly braces              |
| file suffixes        | Use `.hpp` for header files and `.cpp` for implementations |
| variable prefixes    | class or instance variables should be prefixed with `p_`   |
| class and struct     | struct if only public members                              |
