/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/util/solver.hpp
/// @brief Definition and declaration of solving linear equation systems
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_UTIL_SOLVER_HPP
#define LA_ALGORITHM_UTIL_SOLVER_HPP

#include "la/data_structure/util/concepts.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <cstddef>

namespace la {
namespace algorithm {
namespace util {

/// @brief All solvers operates on matrix- and vector-like types and provide a function to solve
/// linear equation systems
/// @tparam MatT matrix-like type of defining the coefficients of the equation system
/// @tparam VecT vector-like type for right hand side and the solution
template <typename MatT, typename VecT>
class solver
{
private:
    /// @brief matrix type must define value_type
    static_assert(la::util::has_value_type<MatT>, "MatT must define value_type");
    /// @brief vector type must define value_type
    static_assert(la::util::has_value_type<VecT>, "VecT must define value_type");
    /// @brief matrix type and vector type must define the same value_type
    static_assert(la::util::same_value_type<MatT, VecT>, "VecT and MatT must have same value_type");

public:
    /// @brief Type of every element
    typedef typename MatT::value_type value_type;

protected:
    /// @brief Reference to the matrix A (as those are always denoted with capital A, w break our
    /// naming schema here)
    const MatT &p_A;

public:
    /// @brief Default constructor
    solver(const MatT &A) : p_A(A) {}

    /// @brief Default copy constructor
    solver(const solver<MatT, VecT> &solver) : p_A(solver.p_A) {}

    /// @brief Default destructor
    virtual ~solver() = default;

    /// @brief Solve the system with given rhs
    /// @param x A^-1*rhs
    /// @param rhs right hand side
    virtual bool solve(const VecT &b, VecT &x) const = 0;

    /// @brief Solve the system with rhs (constructs a vector for solution)
    /// @param rhs right hand side
    /// @return A^-1*rhs
    VecT solve(const VecT &b) const;
};

/// @brief Class for solvers of dense linear equation systems
template <typename MatT, typename VecT>
class dense_solver : public solver<MatT, VecT>
{
private:
    static_assert(la::util::has_vals_access<MatT>, "MatT must implement vals() access");
    static_assert(la::util::has_row_element_access<VecT>,
                  "VecT must implement operator()(size_type)");

public:
    /// @brief Set me up, basically, do type checks and store reference to the matrix
    dense_solver(const MatT &A) : solver<MatT, VecT>(A) {}

    /// @brief Default copy constructor
    dense_solver(const dense_solver<MatT, VecT> &solver) : solver<MatT, VecT>(solver.p_A) {}

    /// @brief Default destructor
    ~dense_solver() = default;
};

/// @brief Basic iterative solver
template <typename MatT, typename VecT>
class iterative_solver : public solver<MatT, VecT>
{
protected:
    /// @brief Residuum
    double p_res;

    /// @brief Maximal number of iterations
    size_type p_max_iter;

    /// @brief Residuum of last solve
    mutable double p_last_res;

    /// @brief Last number of iterations
    mutable size_type p_last_iter;

    /// @brief Last time solved?
    mutable bool p_last_solved;

public:
    /// @brief Constructor with given residuum and maximum number of iterations
    iterative_solver(const MatT &A, const double res, const size_type max_iter);

    /// @brief Copy constructor
    iterative_solver(const iterative_solver<MatT, VecT> &solver);

    /// @brief Destructor
    ~iterative_solver() = default;

    /// @brief Residuum of last solve
    double res() const { return p_last_res; }

    /// @brief Number of iterations of last solve
    size_type iter() { return p_last_iter; }

    /// @brief Last time solved?
    bool solved() { return p_last_solved; }
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// solver
// ------

template <typename MatT, typename VecT>
VecT solver<MatT, VecT>::solve(const VecT &b) const
{
    SHAPE_ASSERT(p_A.rows() == b.rows(), "Invalid dimension for solving a linear system");
    VecT x(p_A.cols());
    bool solved = solve(b, x);
    if (!solved) {
        LOG_WARNING("System has not been solved");
    }
    return x;
}

// iterative_solver
// ----------------

template <typename MatT, typename VecT>
iterative_solver<MatT, VecT>::iterative_solver(const MatT &A, const double res,
                                               const size_type max_iter)
    : solver<MatT, VecT>(A), p_res(res), p_max_iter(max_iter)
{}

template <typename MatT, typename VecT>
iterative_solver<MatT, VecT>::iterative_solver(const iterative_solver<MatT, VecT> &solver)
    : solver<MatT, VecT>(solver.p_A), p_res(solver.p_res), p_max_iter(solver.p_max_iter)
{}

} // namespace util
} // namespace algorithm
} // namespace la
#endif
