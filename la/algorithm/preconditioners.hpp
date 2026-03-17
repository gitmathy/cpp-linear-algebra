/// Part of the project "cpp-linear-algebra"
///
/// @file la/algorithm/preconditioners.hpp
/// @brief Definition and declaration of pre-conditioner classes for sparse linear equation systems
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_ALGORITHM_PRECONDITIONER_HPP
#define LA_ALGORITHM_PRECONDITIONER_HPP

#include "la/algorithm/util/solver.hpp"
#include "la/data_structure/util/concepts.hpp"
#include "la/util/types.hpp"
#include <cstddef>

namespace la {
namespace algorithm {

template <typename MatT, typename VecT>
class jacobi_pc : public util::preconditioner<MatT, VecT>
{
public:
    /// @brief Type of every element
    typedef typename util::preconditioner<MatT, VecT>::value_type value_type;

private:
    /// @brief Scaled inverted diagonal elements of A (omega /a_ii)
    VecT p_scaled_inv_diag;

public:
    /// @brief Set diagonal elements
    jacobi_pc(const MatT &A, const value_type &omega);

    /// @brief Copy constructor
    jacobi_pc(const jacobi_pc<MatT, VecT> &jac);

    /// @brief Apply the preconditioner
    bool solve(const VecT &b, VecT &x) const;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::preconditioner<MatT, VecT>::solve;
};

template <typename MatT, typename VecT>
class symmetric_gauss_seidel_pc : public util::preconditioner<MatT, VecT>
{
private:
    /// @brief matrix type must define value_type
    static_assert(la::util::has_row_idx_begin<MatT>, "MatT additionally grant access to rows");
    static_assert(la::util::has_col_idx<MatT>, "MatT additionally grant access to column indices");
    static_assert(la::util::has_nnz_access<MatT>, "MatT additionally grant access to non-zeros");

public:
    /// @brief Type of every element
    typedef typename util::preconditioner<MatT, VecT>::value_type value_type;

private:
    /// @brief Scaled inverted diagonal elements of A (omega /a_ii)
    VecT p_scaled_inv_diag;

public:
    /// @brief Set diagonal elements
    symmetric_gauss_seidel_pc(const MatT &A, const value_type &omega);

    /// @brief Copy constructor
    symmetric_gauss_seidel_pc(const symmetric_gauss_seidel_pc<MatT, VecT> &jac);

    /// @brief Apply the preconditioner
    bool solve(const VecT &b, VecT &x) const;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::preconditioner<MatT, VecT>::solve;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// jacobi_pc
// ---------

template <typename MatT, typename VecT>
jacobi_pc<MatT, VecT>::jacobi_pc(const MatT &A,
                                 const typename jacobi_pc<MatT, VecT>::value_type &omega)
    : util::preconditioner<MatT, VecT>(A, omega), p_scaled_inv_diag(A.rows())
{
    // set diagonal elements
    for (size_type i = 0; i < A.rows(); ++i) {
        p_scaled_inv_diag(i) = A(i, i);
        NON_ZERO_ASSERT(p_scaled_inv_diag(i), "diagonal element of matrix is zero");
    }
}

template <typename MatT, typename VecT>
jacobi_pc<MatT, VecT>::jacobi_pc(const jacobi_pc<MatT, VecT> &jac)
    : util::preconditioner<MatT, VecT>(jac.p_A, jac.p_omega),
      p_scaled_inv_diag(jac.p_scaled_inv_diag)
{}

template <typename MatT, typename VecT>
bool jacobi_pc<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    SHAPE_ASSERT(x.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of result");
    SHAPE_ASSERT(b.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of vector");
    x = b * p_scaled_inv_diag;
    return true;
}

// symmetric_gauss_seidel_pc
// ---------------

template <typename MatT, typename VecT>
symmetric_gauss_seidel_pc<MatT, VecT>::symmetric_gauss_seidel_pc(
    const MatT &A, const typename symmetric_gauss_seidel_pc<MatT, VecT>::value_type &omega)
    : util::preconditioner<MatT, VecT>(A, omega), p_scaled_inv_diag(A.rows())
{
    // set diagonal elements
    for (size_type i = 0; i < A.rows(); ++i) {
        p_scaled_inv_diag(i) = A(i, i);
        NON_ZERO_ASSERT(p_scaled_inv_diag(i), "diagonal element of matrix is zero");
    }
}

template <typename MatT, typename VecT>
symmetric_gauss_seidel_pc<MatT, VecT>::symmetric_gauss_seidel_pc(
    const symmetric_gauss_seidel_pc<MatT, VecT> &jac)
    : util::preconditioner<MatT, VecT>(jac.p_A, jac.p_omega),
      p_scaled_inv_diag(jac.p_scaled_inv_diag)
{}

template <typename MatT, typename VecT>
bool symmetric_gauss_seidel_pc<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    SHAPE_ASSERT(x.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of result");
    SHAPE_ASSERT(b.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of vector");
    typedef typename symmetric_gauss_seidel_pc<MatT, VecT>::value_type T;
    const MatT &A = this->p_A;

    // initialize x
    x = T(0);

    size_type j = 0;
    const size_type n = A.rows();
    T a_ii = T(0);
    T sigma = 0.0;
    // Forward
    for (size_type i = 0; i < n; ++i) {
        sigma = 0;
        for (size_type nz = A.row_idx_begin(i); nz < A.row_idx_begin(i + 1); ++nz) {
            j = A.col_idx(nz);
            if (j != i) {
                sigma += A(nz) * x(j);
            } else {
                a_ii = A(nz);
            }
        }
        x(i) = (b(i) - sigma) / a_ii;
    }

    // 2. Backward Sweep (to ensure symmetry)
    for (int i = int(n) - 1; i >= 0; --i) {
        sigma = 0.0;
        for (size_type nz = A.row_idx_begin(i); nz < A.row_idx_begin(i); ++nz) {
            j = A.col_idx(nz);
            if (i != int(j)) {
                sigma += A(nz) * x(j);
            } else {
                a_ii = A(nz);
            }
        }
        x(i) = (b(i) - sigma) / a_ii;
    }
    return true;
}

} // namespace algorithm
} // namespace la
#endif
