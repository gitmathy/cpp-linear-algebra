#ifndef TEST_LA_TEST_VECTOR_H
#define TEST_LA_TEST_VECTOR_H

#include "includes/unit_test.hpp"
#include <sstream>
#include <typeinfo>

namespace la_test
{

/// @brief Testing vector
class vector_test : public unit_test
{
private:
    /// @brief Test constructing a vector
    template <typename T> bool test_construct();

    /// @brief Test resizing a vector
    template <typename T> bool test_resize();

    bool test_various_constructs();

public:
    /// @brief Setup the vector test
    vector_test();
    /// @brief Destruct the vector test
    ~vector_test() = default;

    /// @brief Execute the test
    /// @return True if test succeeded
    bool execute() override;
};

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T> bool vector_test::test_construct()
{
    bool result = true;
    // construct with defaults
    la::vector<T> *v = new la::vector<double>(3, T(2));
    for (::la::size_type i = 0; i < v->size(); ++i)
    {
        if (double((*v)(i)-2) > 1e-16)
        {
            result = false;
        }
    }
    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << std::typeid(T()).name() << "> error in constructor";
        p_errors.push_back(strs.str());
        p_logger.log(strs.str(), ERROR);
    }
    // destruct
    delete v;
    return result;
}

/// @brief Test resizing a vector
template <typename T> bool vector_test::test_resize() {}

} // namespace la_test
#endif
