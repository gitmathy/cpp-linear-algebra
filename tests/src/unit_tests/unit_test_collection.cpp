/// Part of the project "cpp-linear-algebra"
///
/// @file tests/src/unit_tests/unit_test_collection.cpp
/// @brief Definition of unit test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#include "tests/includes/unit_tests/unit_test_collection.hpp"
#include "tests/includes/unit_test.hpp"

namespace la {
namespace test {

void unit_test_collection::report(const std::set<std::string> &label_filter)
{
    std::stringstream strs;
    strs << "\n----------------------------------------\n";
    strs << "    ERROR REPORT: " << p_name << '\n';
    strs << "----------------------------------------";
    this->log(strs, INFO);

    for (auto &labeled : p_tests) {
        if (label_in_filter(labeled.first, label_filter)) {
            for (auto &test : labeled.second) {
                const unit_test *const unit_test_p = dynamic_cast<unit_test *>(test.get());
                if (unit_test_p->failed()) {
                    for (auto &error : unit_test_p->errors()) {
                        strs << "* [" << test->name() << "]: " << error << '\n';
                    }
                    this->log(strs, INFO);
                }
            }
        }
    }
    this->log("----------------------------------------", INFO);
}

} // namespace test
} // namespace la
