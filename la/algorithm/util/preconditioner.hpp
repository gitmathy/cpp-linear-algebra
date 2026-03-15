/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/util/preconditioner.hpp
/// @brief Definition and declaration of pre-conditioner for sparse linear equation systems
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_UTIL_PRECONDITIONER_HPP
#define LA_ALGORITHM_UTIL_PRECONDITIONER_HPP

#include "la/algorithm/util/solver.hpp"
#include "la/data_structure/util/concepts.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <cstddef>

namespace la {
namespace algorithm {
namespace util {

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
    /// @brief matrix type must define value_type
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

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

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

} // namespace util
} // namespace algorithm
} // namespace la
#endif
