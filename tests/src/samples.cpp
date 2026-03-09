/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/samples.cpp
/// @brief Implementation of sample providing
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/samples.hpp"

namespace la {
namespace test {

std::shared_ptr<sample_la_structures<double>>
get_default_samples(size_type vec_rows, size_type mat_rows, size_type mat_cols,
                    size_type sparse_size, size_type max_nn_per_row)
{
    static std::shared_ptr<sample_la_structures<double>> defaults(nullptr);
    if (defaults == nullptr) {
        defaults = std::make_shared<sample_la_structures<double>>(vec_rows, mat_rows, mat_cols,
                                                                  sparse_size, max_nn_per_row);
    }
    return defaults;
}

} // namespace test
} // namespace la
