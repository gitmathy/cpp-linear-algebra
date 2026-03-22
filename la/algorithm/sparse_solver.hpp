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
#include "la/data_structure/matrix.hpp"
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
    typedef typename util::solver<MatT, VecT>::value_type value_type;

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

/// @brief Preconditioned restarted gmres solver
template <typename MatT, typename VecT, typename PreconditionerLeftT, typename PreconditionerRightT>
class pgmres_solver
    : public util::two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT,
                                                            PreconditionerRightT>
{
public:
    typedef typename util::solver<MatT, VecT>::value_type value_type;

private:
    /// @brief Restart parameter
    size_type p_restart;

public:
    /// @brief Set up a preconditioned gmres solver
    pgmres_solver(const MatT &A, const double res, const size_type max_iter, size_type restart,
                  const typename util::solver<MatT, VecT>::value_type omega = 1.0);

    /// @brief Copying a pgmres solver
    pgmres_solver(
        const pgmres_solver<MatT, VecT, PreconditionerLeftT, PreconditionerRightT> &solver);

    /// @brief Apply the preconditioning
    bool solve(const VecT &b, VecT &x) const override;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT,
                                                         PreconditionerRightT>::solve;
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
                 "Invalid dimension for cg solve");
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
    : util::preconditioned_iterative_solver<MatT, VecT, PreconditionerT>(solver)
{}

template <typename MatT, typename VecT, typename PreconditionerT>
bool pcg_solver<MatT, VecT, PreconditionerT>::solve(const VecT &b, VecT &x) const
{
    SHAPE_ASSERT(b.rows() == this->p_A.rows() && x.rows() == this->p_A.cols(),
                 "Invalid dimension for preconditioned cg solve");
    LOG_INFO("Solving linear equation system (" << b.rows() << ") with preconditioned CG");
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
        M.solve(r, z);
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

// pgmres_solver
// -------------

template <typename MatT, typename VecT, typename PreconditionerLeftT, typename PreconditionerRightT>
pgmres_solver<MatT, VecT, PreconditionerLeftT, PreconditionerRightT>::pgmres_solver(
    const MatT &A, const double res, const size_type max_iter, size_type restart,
    const typename util::solver<MatT, VecT>::value_type omega)
    : util::two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT,
                                                     PreconditionerRightT>(A, res, max_iter, omega),
      p_restart(restart)
{}

template <typename MatT, typename VecT, typename PreconditionerLeftT, typename PreconditionerRightT>
pgmres_solver<MatT, VecT, PreconditionerLeftT, PreconditionerRightT>::pgmres_solver(
    const pgmres_solver<MatT, VecT, PreconditionerLeftT, PreconditionerRightT> &solver)
    : util::two_side_preconditioned_iterative_solver<MatT, VecT, PreconditionerLeftT,
                                                     PreconditionerRightT>(solver),
      p_restart(solver.p_restart)
{}

template <typename MatT, typename VecT, typename PreconditionerLeftT, typename PreconditionerRightT>
bool pgmres_solver<MatT, VecT, PreconditionerLeftT, PreconditionerRightT>::solve(const VecT &b,
                                                                                 VecT &x) const
{
    SHAPE_ASSERT(b.rows() == this->p_A.rows() && x.rows() == this->p_A.cols(),
                 "Invalid dimension for gmres solve");
    LOG_INFO("Solving linear equation system (" << this->p_A.rows() << " x " << this->p_A.cols()
                                                << ") with preconditioned gmres");
    typedef typename util::iterative_solver<MatT, VecT>::value_type T;

    // references to members of base class to avoid "virtual lookups"
    const MatT &A = this->p_A;
    const PreconditionerLeftT &ML = this->p_M_left;
    const PreconditionerRightT &MR = this->p_M_right;
    const size_type max_iter = this->p_max_iter;
    const size_type n = A.rows();
    const T &tol = this->p_res;
    VecT r(n), w(n), update(n), z(n), tmp(n); // helper vectors
    size_type iter = 0;
    T obtained_tol = 0.;
    std::vector<VecT> V(p_restart + 1, VecT(n));
    matrix<T> H(p_restart + 1, p_restart);
    VecT sn(p_restart, 0.0), cs(p_restart, 0.0);

    LOG_DEBUG("Starting with gmres iterations");
    for (iter = 0; iter < max_iter; ++iter) {
        // Initial residual: r = M_left.solve(b - A * x)
        tmp = b - A * x;
        ML.solve(tmp, r);
        const T beta = norm<2>(r);

        if (beta < tol) {
            obtained_tol = beta;
            break;
        } else {
            LOG_DEBUG("Relative error norm: " << beta);
        }
        V[0] = r * (1.0 / beta);

        VecT g(p_restart + 1, 0.0);
        g(0) = beta;

        size_type j = 0;
        LOG_DEBUG("Starting next restart");
        for (; j < p_restart; ++j) {
            // Arnoldi with both Preconditioners: w = ML.solve(A * MR.solve(V[j]))
            MR.solve(V[j], z);
            tmp = A * z;
            ML.solve(tmp, w);

            // Modified Gram-Schmidt
            for (size_type i = 0; i <= j; ++i) {
                H(i, j) = inner_product(w, V[i]);
                w = w - V[i] * H(i, j);
            }
            H(j + 1, j) = norm<2>(w);
            V[j + 1] = w * (1.0 / H(j + 1, j));

            // Apply existing Givens rotations
            for (size_type i = 0; i < j; ++i) {
                const T temp = cs(i) * H(i, j) + sn(i) * H(i + 1, j);
                H(i + 1, j) = -sn(i) * H(i, j) + cs(i) * H(i + 1, j);
                H(i, j) = temp;
            }

            // New Givens rotation
            const T t = std::sqrt(H(j, j) * H(j, j) + H(j + 1, j) * H(j + 1, j));
            cs(j) = H(j, j) / t;
            sn(j) = H(j + 1, j) / t;

            H(j, j) = cs(j) * H(j, j) + sn(j) * H(j + 1, j);
            g(j + 1) = -sn(j) * g(j);
            g(j) = cs(j) * g(j);

            if (std::abs(g(j + 1)) < tol) {
                j++;
                break;
            }
        }

        // Back-solve Hy = g
        VecT y(j);
        for (signed_size_type i = (signed_size_type)j - 1; i >= 0; --i) {
            T sum = 0.0;
            for (size_type k = i + 1; k < j; ++k) {
                sum += H(i, k) * y(k);
            }
            y(i) = (g(i) - sum) / H(i, i);
        }

        // Update x: x = x + MR.solve(V * y)
        update = T(0);
        for (size_type i = 0; i < j; ++i) {
            update = update + V[i] * y(i);
        }
        MR.solve(update, z);
        x += z;

        if (std::abs(g(j)) < tol) {
            obtained_tol = std::abs(g(j));
        }
    }
    if (iter < max_iter) {
        LOG_INFO("GMRES converged in " << iter << " iterations");
        this->p_last_solved = (iter < max_iter);
        this->p_last_res = obtained_tol;
        this->p_last_iter = iter;
    }

    return this->p_last_solved;
}

} // namespace algorithm
} // namespace la
#endif
