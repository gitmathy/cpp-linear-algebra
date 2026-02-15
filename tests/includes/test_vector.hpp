#ifndef TEST_LA_TEST_VECTOR_H
#define TEST_LA_TEST_VECTOR_H

#include "../includes/la.hpp"
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

    /// @brief Test copy-assignment operator
    template <typename T> bool test_copy_assignment();

    /// @brief Test move-assignment operator
    template <typename T> bool test_move_assignment();

    /// @brief Test add/sub assignment operators (+=, -=)
    template <typename T> bool test_add_sub_assignment();

    /// @brief Test add/sub operators (+, -)
    template <typename T> bool test_add_sub_ops();

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
    for (la::size_type i = 0; i < v->rows(); ++i)
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
    if (v.rows() != 5)
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
    if (v.rows() != 4)
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
    for (la::size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<T>(i * 10 + 1);
    la::vector<T> dst(std::move(src));
    if (dst.rows() != 4)
    {
        result = false;
        p_logger.log("Moved-to vector has incorrect size", ERROR);
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
    {
        if (double(dst(i) - static_cast<T>(i * 10 + 1)) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "Moved-to vector has incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    if (src.rows() != 0)
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

// ------------------------------------------------------------------
// Copy-assignment test
// ------------------------------------------------------------------
template <typename T> bool vector_test::test_copy_assignment()
{
    bool result = true;

    la::vector<T> src(4);
    for (la::size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<T>(i * 3 + 2);

    la::vector<T> dst(2, T(0));
    dst = src; // copy-assign

    // dst must match src
    if (dst.rows() != src.rows())
    {
        result = false;
        p_logger.log("Copy-assigned vector has incorrect size", ERROR);
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
    {
        if (double(dst(i) - src(i)) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "Copy-assigned vector has incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // source must remain unchanged
    for (la::size_type i = 0; i < src.rows(); ++i)
    {
        if (double(src(i) - static_cast<T>(i * 3 + 2)) != 0.0)
        {
            result = false;
            p_logger.log("Source vector changed after copy-assignment", ERROR);
            break;
        }
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(T()).name() << "> error in copy assignment";
        p_errors.push_back(strs.str());
    }

    return result;
}

// ------------------------------------------------------------------
// Move-assignment test
// ------------------------------------------------------------------
template <typename T> bool vector_test::test_move_assignment()
{
    bool result = true;

    la::vector<T> src(4);
    for (la::size_type i = 0; i < src.rows(); ++i)
        src(i) = static_cast<T>(i * 5 + 7);

    la::vector<T> dst(2, T(9));
    dst = std::move(src);

    // dst must contain values
    if (dst.rows() != 4)
    {
        result = false;
        p_logger.log("Move-assigned vector has incorrect size", ERROR);
    }
    for (la::size_type i = 0; i < dst.rows(); ++i)
    {
        if (double(dst(i) - static_cast<T>(i * 5 + 7)) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "Move-assigned vector has incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // moved-from should be in valid empty state
    if (src.rows() != 0)
    {
        result = false;
        p_logger.log("Moved-from vector not left empty after move-assignment", ERROR);
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(T()).name() << "> error in move assignment";
        p_errors.push_back(strs.str());
    }

    return result;
}

// ------------------------------------------------------------------
// Add/Sub assignment operators (+=, -=)
// ------------------------------------------------------------------
template <typename T> bool vector_test::test_add_sub_assignment()
{
    bool result = true;

    la::vector<T> a(3), b(3);
    for (la::size_type i = 0; i < a.rows(); ++i)
    {
        a(i) = static_cast<T>(i + 1);        // 1,2,3
        b(i) = static_cast<T>((i + 1) * 10); // 10,20,30
    }

    la::vector<T> a_orig(a.rows());
    a_orig = a;
    la::vector<T> b_orig(b.rows());
    b_orig = b;

    // test += with a plain vector RHS
    a += b;
    for (la::size_type i = 0; i < a.rows(); ++i)
    {
        if (double(a(i) - (a_orig(i) + b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "+= produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    // rhs must remain unchanged
    for (la::size_type i = 0; i < b.rows(); ++i)
    {
        if (double(b(i) - b_orig(i)) != 0.0)
        {
            result = false;
            p_logger.log("Right-hand side modified by +=", ERROR);
            break;
        }
    }

    // test -= with a plain vector RHS
    la::vector<T> c(a_orig.rows());
    c = a_orig; // reset via assignment
    c -= b_orig;
    for (la::size_type i = 0; i < c.rows(); ++i)
    {
        if (double(c(i) - (a_orig(i) - b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "-= produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }

    // -------------------------
    // New: tests where RHS is an expression
    // -------------------------

    // 1) operator+= with RHS = (a_orig - b_orig)  (vector temporary)
    a = a_orig; // reset lhs
    {
        la::vector<T> rhs = a_orig - b_orig; // evaluate temporary
        a += rhs;
        for (la::size_type i = 0; i < a.rows(); ++i)
        {
            T expected = a_orig(i) + rhs(i); // a_orig + (a_orig - b_orig)
            if (double(a(i) - expected) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "+= with expression (vector temporary) produced incorrect value at " << i;
                p_logger.log(ss.str(), ERROR);
            }
        }
        // rhs must remain unchanged
        for (la::size_type i = 0; i < rhs.rows(); ++i)
        {
            if (double(rhs(i) - (a_orig(i) - b_orig(i))) != 0.0)
            {
                result = false;
                p_logger.log("Right-hand side modified by += (vector temporary)", ERROR);
                break;
            }
        }
    }

    // 2) operator+= with RHS = (a_orig + b_orig)  (expression -> operant -> converted to vector temporary)
    a = a_orig; // reset lhs
    {
        a += a_orig + b_orig; // RHS is an expression (operant); should convert to temporary vector
        for (la::size_type i = 0; i < a.rows(); ++i)
        {
            T expected = a_orig(i) + (a_orig(i) + b_orig(i)); // a_orig + (a_orig + b_orig)
            if (double(a(i) - expected) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "+= with expression (operant) produced incorrect value at " << i;
                p_logger.log(ss.str(), ERROR);
            }
        }
        // ensure operands were not modified
        for (la::size_type i = 0; i < a_orig.rows(); ++i)
        {
            if (double(a_orig(i) - static_cast<T>(i + 1)) != 0.0 ||
                double(b_orig(i) - static_cast<T>((i + 1) * 10)) != 0.0)
            {
                result = false;
                p_logger.log("An operand was modified by +=(expression)", ERROR);
                break;
            }
        }
    }

    // 3) operator-= with RHS = (a_orig + b_orig)  (expression -> operant -> converted to vector temporary)
    c = a_orig; // reset
    {
        c -= a_orig + b_orig;
        for (la::size_type i = 0; i < c.rows(); ++i)
        {
            T expected = a_orig(i) - (a_orig(i) + b_orig(i));
            if (double(c(i) - expected) != 0.0)
            {
                result = false;
                std::stringstream ss;
                ss << "-= with expression (operant) produced incorrect value at " << i;
                p_logger.log(ss.str(), ERROR);
            }
        }
        // ensure operands were not modified
        for (la::size_type i = 0; i < a_orig.rows(); ++i)
        {
            if (double(a_orig(i) - static_cast<T>(i + 1)) != 0.0 ||
                double(b_orig(i) - static_cast<T>((i + 1) * 10)) != 0.0)
            {
                result = false;
                p_logger.log("An operand was modified by -=(expression)", ERROR);
                break;
            }
        }
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(T()).name() << "> error in add/sub assignment";
        p_errors.push_back(strs.str());
    }

    return result;
}

// ------------------------------------------------------------------
// Add/Sub operators (+, -)
// ------------------------------------------------------------------
template <typename T> bool vector_test::test_add_sub_ops()
{
    bool result = true;

    la::vector<T> a(3), b(3);
    for (la::size_type i = 0; i < a.rows(); ++i)
    {
        a(i) = static_cast<T>(i + 2);       // 2,3,4
        b(i) = static_cast<T>((i + 1) * 5); // 5,10,15
    }

    la::vector<T> a_orig(a.rows());
    a_orig = a;
    la::vector<T> b_orig(b.rows());
    b_orig = b;

    // test + (returns new vector, lhs/rhs unchanged)
    la::vector<T> sum = a + b;
    for (la::size_type i = 0; i < sum.rows(); ++i)
    {
        if (double(sum(i) - (a_orig(i) + b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "+ produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    if (double(a(0) - a_orig(0)) != 0.0 || double(b(0) - b_orig(0)) != 0.0)
    {
        result = false;
        p_logger.log("Operands modified by +", ERROR);
    }

    // test - (returns new vector, lhs/rhs unchanged)
    la::vector<T> diff = a - b;
    for (la::size_type i = 0; i < diff.rows(); ++i)
    {
        if (double(diff(i) - (a_orig(i) - b_orig(i))) != 0.0)
        {
            result = false;
            std::stringstream ss;
            ss << "- produced incorrect value at " << i;
            p_logger.log(ss.str(), ERROR);
        }
    }
    if (double(a(0) - a_orig(0)) != 0.0 || double(b(0) - b_orig(0)) != 0.0)
    {
        result = false;
        p_logger.log("Operands modified by -", ERROR);
    }

    if (!result)
    {
        std::stringstream strs;
        strs << "vector<" << typeid(T()).name() << "> error in add/sub operators";
        p_errors.push_back(strs.str());
    }

    return result;
}

} // namespace la_test
#endif
