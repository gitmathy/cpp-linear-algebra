/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/dense_solver.hpp
/// @brief Definition and declaration of solvers for sparse linear equation systems
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_SPARSE_SOLVER_HPP
#define LA_ALGORITHM_SPARSE_SOLVER_HPP

#include "la/algorithm/util/solver.hpp"
#include "la/data_structure/util/concepts.hpp"
#include "la/operation/inner_product.hpp"
#include <cmath>

namespace la {
namespace algorithm {

/// @brief Conjugate gradient solver
template <typename MatT, typename VecT>
class cg_solver : public util::iterative_solver<MatT, VecT>
{
public:
    /// @brief Set up a conjugate gradient solver
    cg_solver(const MatT &A, const double res, const size_type max_iter);

    /// @brief Copying a conjugate gradient solver
    cg_solver(const cg_solver<MatT, VecT> &solver);

    /// @brief Solve the system with given rhs
    /// @param x A^-1*rhs
    /// @param rhs right hand side
    bool solve(const VecT &b, VecT &x) const override;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::iterative_solver<MatT, VecT>::solve;
};

/// @brief Preconditioned conjugate gradient solver
template <typename MatT, typename VecT, typename PreconditionerT>
class pcg_solver : public util::preconditioned_iterative_solver<MatT, VecT, PreconditionerT>
{
public:
    typename util::solver<MatT, VecT>::value_type value_type;

public:
    /// @brief Set up a preconditioned conjugate gradient solver
    pcg_solver(const MatT &A, const double res, const size_type max_iter,
               const typename util::solver<MatT, VecT>::value_type omega = 1.0);

    /// @brief Copying a pcg solver
    pcg_solver(const pcg_solver<MatT, VecT, PreconditionerT> &solver);

    /// @brief Apply the preconditioning
    bool solve(const VecT &b, VecT &x) const override;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::preconditioned_iterative_solver<MatT, VecT, PreconditionerT>::solve;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// cg_solver
// ---------

template <typename MatT, typename VecT>
cg_solver<MatT, VecT>::cg_solver(const MatT &A, const double res, const size_type max_iter)
    : util::iterative_solver<MatT, VecT>(A, res, max_iter)
{}

template <typename MatT, typename VecT>
cg_solver<MatT, VecT>::cg_solver(const cg_solver<MatT, VecT> &solver)
    : util::iterative_solver<MatT, VecT>(solver.p_A, solver.p_res, solver.p_max_iter)
{}

template <typename MatT, typename VecT>
bool cg_solver<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    SHAPE_ASSERT(b.rows() == this->p_A.rows() && x.rows() == this->p_A.cols(),
                 "Invalid dimension for LU solve");
    LOG_INFO("Solving linear equation system (" << b.rows() << ") with un-preconditioned CG");
    typedef typename util::iterative_solver<MatT, VecT>::value_type T;

    // references to members of base class to avoid "virtual lookups"
    const MatT &A = this->p_A;
    const T res = T(this->p_res);
    const size_type max_iter = this->p_max_iter;
    size_type &last_iter = this->p_last_iter;

    VecT r = b - A * x; // initial residual
    VecT p = r,         // initial search direction
        Ap(A.rows());   // allocate memory for A*p once.
    T res_old = inner_product(r, r);
    for (last_iter = 0; last_iter < max_iter; ++last_iter) {
        Ap = A * p;
        const T alpha = res_old / inner_product(p, Ap);
        LOG_DEBUG("Update solution by alpha=" << alpha);
        x += alpha * p;
        r -= alpha * Ap;
        const T res_new = inner_product(r, r);
        if (std::sqrt(res_new) < res) {
            LOG_INFO("CG converged in " << last_iter + 1 << " iterations.");
            res_old = res_new;
            break;
        }
        const T beta = res_new / res_old;
        LOG_DEBUG("Update search directionby beta=" << beta);
        p = r + beta * p;
        res_old = res_new;
    }
    this->p_last_solved = (last_iter < max_iter);
    if (!this->p_last_solved) {
        LOG_WARNING("CG algorithm didn't converged");
    }
    this->p_last_res = std::sqrt(res_old);
    return this->p_last_solved;
}

// pcg_solver
// ----------

template <typename MatT, typename VecT, typename PreconditionerT>
pcg_solver<MatT, VecT, PreconditionerT>::pcg_solver(
    const MatT &A, const double res, const size_type max_iter,
    const typename util::solver<MatT, VecT>::value_type omega)
    : util::preconditioned_iterative_solver<MatT, VecT, PreconditionerT>(A, res, max_iter, omega)
{}

template <typename MatT, typename VecT, typename PreconditionerT>
pcg_solver<MatT, VecT, PreconditionerT>::pcg_solver(
    const pcg_solver<MatT, VecT, PreconditionerT> &solver)
    : util::preconditioned_iterative_solver<MatT, VecT, PreconditionerT>(
          solver.p_A, solver.p_res, solver.p_max_iter, solver.p_omega)
{}

template <typename MatT, typename VecT, typename PreconditionerT>
bool pcg_solver<MatT, VecT, PreconditionerT>::solve(const VecT &b, VecT &x) const
{
    SHAPE_ASSERT(b.rows() == this->p_A.rows() && x.rows() == this->p_A.cols(),
                 "Invalid dimension for LU solve");
    LOG_INFO("Solving linear equation system (" << b.rows() << ") with un-preconditioned CG");
    typedef typename pcg_solver<MatT, VecT, PreconditionerT>::value_type T;

    // references to members of base class to avoid "virtual lookups"
    const MatT &A = this->p_A;
    const T res = T(this->p_res);
    const size_type max_iter = this->p_max_iter;
    size_type &last_iter = this->p_last_iter;
    const PreconditionerT &M = this->p_M;

    VecT r = b - A * x; // initial residual
    VecT z = M.solve(r);
    VecT p = z,       // initial search direction
        Ap(A.rows()); // allocate memory for A*p once.
    T preconditioned_res_old = inner_product(r, z);
    T res_old = inner_product(r, r);
    T inital_res = res_old;

    for (last_iter = 0; last_iter < max_iter; ++last_iter) {
        Ap = A * p;
        const T alpha = preconditioned_res_old / inner_product(p, Ap);
        LOG_DEBUG("Update solution by alpha=" << alpha);
        x += alpha * p;
        r -= alpha * Ap;
        const T res_new = inner_product(r, r);
        if (std::sqrt(res_new) < res * inital_res) {
            LOG_INFO("CG converged in " << last_iter + 1 << " iterations.");
            res_old = res_new;
            break;
        }
        z = M.solve(r);
        const T preconditioned_res_new = inner_product(r, z);
        const T beta = preconditioned_res_new / preconditioned_res_old;
        LOG_DEBUG("Update search directionby beta=" << beta);
        p = z + beta * p;
        preconditioned_res_old = preconditioned_res_new;
    }
    this->p_last_solved = (last_iter < max_iter);
    if (!this->p_last_solved) {
        LOG_WARNING("CG algorithm didn't converged");
    }
    this->p_last_res = std::sqrt(res_old);
    return this->p_last_solved;
}

} // namespace algorithm
} // namespace la
#endif
