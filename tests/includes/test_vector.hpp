#ifndef TEST_LA_TEST_VECTOR_H
#define TEST_LA_TEST_VECTOR_H

#include "../includes/vector.hpp"
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

    /// @brief Test move constructor
    template <typename T> bool test_move_constructor();

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
    la::vector<T> *v = new la::vector<T>(3, T(2));
    for (la::size_type i = 0; i < v->size(); ++i)
    {
        if (double((*v)(i)-2) > 1e-16)
        {
            result = false;
        }
    }
    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(T()).name() << "> error in constructor";
        p_errors.push_back(strs.str());
        p_logger.log(strs.str(), ERROR);
    }
    // destruct
    delete v;
    return result;
}

/// @brief Test resizing a vector
template <typename T> bool vector_test::test_resize()
{
    bool result = true;
    la::vector<T> v(3);
    v.resize(5, T(100));
    if (double(v(4) - 100) > 1e-16)
    {
        result = false;
        p_logger.log("Default value not set when making vector bigger", ERROR);
    }
    if (v.size() != 5)
    {
        result = false;
        p_logger.log("Incorrect size when making vector bigger", ERROR);
    }
    v.resize(4);
    if (double(v(3) - 100) > 1e-16)
    {
        result = false;
        p_logger.log("Value not kept when making vector smaler", ERROR);
    }
    if (v.size() != 4)
    {
        result = false;
        p_logger.log("Incorrect size when making vector smaler", ERROR);
    }
    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(T()).name() << "> error in resize";
        p_errors.push_back(strs.str());
    }

    return result;
}

template <typename T> bool vector_test::test_move_constructor()
{
    bool result = true;
    la::vector<T> src(4);
    for (la::size_type i = 0; i < src.size(); ++i)
        src(i) = static_cast<T>(i * 10 + 1);
    la::vector<T> dst(std::move(src));
    if (dst.size() != 4)
    {
        result = false;
        p_logger.log("Moved-to vector has incorrect size", ERROR);
    }
    for (la::size_type i = 0; i < dst.size(); ++i)
    {
        if (double(dst(i) - static_cast<T>(i * 10 + 1)) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "Moved-to vector has incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    if (src.size() != 0)
    {
        result = false;
        p_logger.log("Moved-from vector not left in empty state (expected size==0)", ERROR);
    }
    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(T()).name() << "> error in move constructor";
        p_errors.push_back(strs.str());
    }
    return result;
}

} // namespace la_test
#endif
