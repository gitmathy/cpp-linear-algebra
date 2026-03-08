/// Part of the project "cpp-linear-algebra"
///
/// @file tests/includes/collection.hpp
/// @brief Definition of test collection
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_TEST_INCLUDES_COLLECTION_HPP
#define LA_TEST_INCLUDES_COLLECTION_HPP

#include "la/util/types.hpp"
#include "tests/includes/base_test.hpp"
#include "tests/includes/samples.hpp"
#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

namespace la {
namespace test {

/// @brief Base class for all test collections
class test_collection
{
protected:
    /// @brief Name of the collection
    std::string p_name;

    /// @brief All tests are stored by a label and all the tests of the label
    std::unordered_map<std::string, std::list<std::unique_ptr<base_test>>> p_tests;

    /// @brief Logger used for logging
    logger &p_logger;

    /// @brief Get the total number of tests
    size_type numer_of_tests(const std::set<std::string> &label_filter) const;

    /// @brief Wrapping calls to the logger
    void log(const std::string &what, const TestLogLevel &level) { p_logger.log(what, level); }

    /// @brief Wrapping calls to the logger
    void log(std::stringstream &what, const TestLogLevel &level) { p_logger.log(what, level); }

    /// @brief Specialized reportings
    virtual void report(const std::set<std::string> &label_filter) = 0;

    /// @brief Get the number of characters of the longest name of a test
    size_type max_name_length(const std::set<std::string> &label_filter) const;

    /// @brief Get the number of characters of the longest label
    size_type max_label_length(const std::set<std::string> &label_filter) const;

public:
    /// @brief Setup a test collection with a given name
    test_collection(const std::string &name) : p_name(name), p_tests(), p_logger(logger::get()) {}

    /// @brief Default destructor
    virtual ~test_collection() = default;

    /// @brief Move a test to the collection
    void transfer(const std::string &label, std::unique_ptr<base_test> new_test);

    /// @brief Execute all tests
    /// @return Sum of all single executions
    int run(const std::set<std::string> &label_filter = std::set<std::string>());
};

// ===============================================
// P U B L I C   F U N C T I O N S
// ===============================================

bool label_in_filter(const std::string &label, const std::set<std::string> &label_filter);

} // namespace test
} // namespace la
#endif
