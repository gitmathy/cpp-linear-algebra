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
    static_assert(la::util::has_nnz_access<VecT>, "VecT must implement operator()(size_type)");

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

/// @brief Preconditioner used for iterative methods
template <typename MatT, typename VecT>
class preconditioner : public solver<MatT, VecT>
{
public:
    typedef typename solver<MatT, VecT>::value_type value_type;

protected:
    /// @brief Damping
    value_type p_omega;

public:
    /// @brief Initialize the preconditioner
    preconditioner(const MatT &A, const value_type &omega);

    /// @brief Copying a preconditioner
    preconditioner(const preconditioner<MatT, VecT> &M);
};

/// @brief Base class for preconditioned iterative solvers
template <typename MatT, typename VecT, typename PreconditionerT>
class preconditioned_iterative_solver : public iterative_solver<MatT, VecT>
{
private:
    /// @brief Preconditioner must support solve
    static_assert(la::util::has_solve<PreconditionerT, VecT>, "Preconditioner must support solve");

public:
    /// @brief Type of every element
    typedef typename PreconditionerT::value_type value_type;

protected:
    /// @brief Preconditioner
    PreconditionerT p_M;

public:
    /// @brief Constructor also setup the preconditioner
    preconditioned_iterative_solver(const MatT &A, const double res, const size_type max_iter,
                                    const value_type omega);

    /// @brief Copying a preconditioned solver
    preconditioned_iterative_solver(
        const preconditioned_iterative_solver<MatT, VecT, PreconditionerT> &solver);
};

/// @brief Base class for preconditioned iterative solvers with left and right preconditioning
template <typename MatT, typename VecT, typename PreconditionerLeftT, typename PreconditionerRightT>
class two_side_preconditioned_iterative_solver : public iterative_solver<MatT, VecT>
{
private:
    /// @brief left preconditioner must support solve
    static_assert(la::util::has_solve<PreconditionerLeftT, VecT>,
                  "left preconditioner must support solve");
    /// @brief left preconditioner must support solve
    static_assert(la::util::has_solve<PreconditionerRightT, VecT>,
                  "right preconditioner must support solve");

    static_assert(std::is_same<typename PreconditionerLeftT::value_type,
                               typename PreconditionerRightT::value_type>::value,
                  "Value types of preconditioners must be the same");

public:
    /// @brief Type of every element
    typedef typename PreconditionerLeftT::value_type value_type;

protected:
    /// @brief Preconditioner
    PreconditionerLeftT p_M_left;
    /// @brief Preconditioner
    PreconditionerRightT p_M_right;

public:
    /// @brief Constructor also setup the preconditioner
    two_side_preconditioned_iterative_solver(const MatT &A, const double res,
                                             const size_type max_iter, const value_type omega);

    /// @brief Copying a preconditioned solver
    two_side_preconditioned_iterative_solver(
        const two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT,
                                                       PreconditionerRightT> &solver);
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

// preconditioner
// --------------

template <typename MatT, typename VecT>
preconditioner<MatT, VecT>::preconditioner(const MatT &A,
                                           const preconditioner<MatT, VecT>::value_type &omega)
    : solver<MatT, VecT>(A), p_omega(omega)
{
    SHAPE_ASSERT(A.rows() == A.cols(), "Preconditioner only valid for square matrices");
}

template <typename MatT, typename VecT>
preconditioner<MatT, VecT>::preconditioner(const preconditioner<MatT, VecT> &M)
    : solver<MatT, VecT>(M.p_A), p_omega(M.p_omega)
{}

// preconditioned_iterative_solver
// -------------------------------

template <typename MatT, typename VecT, typename PreconditionerT>
preconditioned_iterative_solver<MatT, VecT, PreconditionerT>::preconditioned_iterative_solver(
    const MatT &A, const double res, const size_type max_iter,
    const typename preconditioned_iterative_solver<MatT, VecT, PreconditionerT>::value_type omega)
    : iterative_solver<MatT, VecT>(A, res, max_iter), p_M(A, omega)
{}

template <typename MatT, typename VecT, typename PreconditionerT>
preconditioned_iterative_solver<MatT, VecT, PreconditionerT>::preconditioned_iterative_solver(
    const preconditioned_iterative_solver<MatT, VecT, PreconditionerT> &solver)
    : iterative_solver<MatT, VecT>(solver.p_A, solver.p_res, solver.p_max_iter), p_M(solver.p_M)
{}

// two_side_preconditioned_iterative_solver
// ----------------------------------------

template <typename MatT, typename VecT, typename PreconditionerLeftT, typename PreconditionerRightT>
two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT, PreconditionerRightT>::
    two_side_preconditioned_iterative_solver(
        const MatT &A, const double res, const size_type max_iter,
        const typename two_side_preconditioned_iterative_solver<
            MatT, VecT, PreconditionerLeftT, PreconditionerRightT>::value_type omega)
    : iterative_solver<MatT, VecT>(A, res, max_iter), p_M_left(A, omega), p_M_right(A, omega)
{}

template <typename MatT, typename VecT, typename PreconditionerLeftT, typename PreconditionerRightT>
two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT, PreconditionerRightT>::
    two_side_preconditioned_iterative_solver(
        const two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT,
                                                       PreconditionerRightT> &solver)
    : iterative_solver<MatT, VecT>(solver.p_A, solver.p_res, solver.p_max_iter),
      p_M_left(solver.p_M_left), p_M_right(solver.p_M_right)
{}

} // namespace util
} // namespace algorithm
} // namespace la
#endif
