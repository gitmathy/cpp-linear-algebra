/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/unit_tests/unit_test_collection.hpp
/// @brief Declaration of unit test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_UNIT_TEST_COLLECTION_HPP
#define LA_TEST_INCLUDES_UNIT_TEST_COLLECTION_HPP

#include "la/util/types.hpp"
#include "tests/includes/collection.hpp"
#include <memory>

namespace la {
namespace test {

/// @brief Dedicated class for collection of unit tests
class unit_test_collection : public test_collection
{
private:
    /// @brief Report all errors
    void report(const std::set<std::string> &label_filter) override;

public:
    /// @brief Constructor
    unit_test_collection() : test_collection("unit tests") {}

    /// @brief Default destructor
    ~unit_test_collection() = default;
};

} // namespace test
} // namespace la
#endif
