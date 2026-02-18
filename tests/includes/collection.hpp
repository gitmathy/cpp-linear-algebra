#ifndef LA_TEST_TEST_COLLECTION_H
#define LA_TEST_TEST_COLLECTION_H

#include "includes/types.hpp"
#include "tests/includes/base_test.hpp"
#include "tests/includes/log.hpp"
#include <list>
#include <memory>
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
    size_type numer_of_tests(const std::string &label) const;

    /// @brief Wrapping calls to the logger
    void log(const std::string &what, const TestLogLevel &level) { p_logger.log(what, level); }

    /// @brief Wrapping calls to the logger
    void log(std::stringstream &what, const TestLogLevel &level) { p_logger.log(what, level); }

    /// @brief Specialized reportings
    virtual void report(const std::string &label_filter) = 0;

public:
    /// @brief Setup a test collection with a given name
    test_collection(const std::string &name) : p_name(name), p_tests(), p_logger(logger::get()) {}

    /// @brief Default destructor
    virtual ~test_collection() = default;

    /// @brief Move a test to the collection
    void transfer(const std::string &label, std::unique_ptr<base_test> new_test);

    /// @brief Execute all tests
    /// @return Sum of all single executions
    int run(const std::string &label_filter = "all");
};

/// @brief Dedicated class for collection of unit tests
class unit_test_collection : public test_collection
{
private:
    /// @brief Report all errors
    void report(const std::string &label_filter) override;

public:
    /// @brief Constructor
    unit_test_collection() : test_collection("unit tests") {}

    /// @brief Default destructor
    ~unit_test_collection() = default;
};

/// @brief Dedicated class for collection of performance tests
class performance_test_collection : public test_collection
{
private:
    /// @brief Number of runs
    size_type p_runs;

    /// @brief Size of vectors
    size_type p_vector_size;

    /// @brief Rows of matrices
    size_type p_matrix_rows;

    /// @brief Columns of matrices
    size_type p_matrix_cols;

    /// @brief Report all timings
    void report(const std::string &label_filter) override;

public:
    /// @brief Constructor
    performance_test_collection(const size_type runs, const size_type vec_n, const size_type mat_m,
                                const size_type mat_n);

    /// @brief Default destructor
    ~performance_test_collection() = default;
};

} // namespace test
} // namespace la
#endif
