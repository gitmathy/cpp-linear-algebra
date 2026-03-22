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
#include "la/util/constants.hpp"
#include "la/util/types.hpp"
#include <cstddef>

namespace la {
namespace algorithm {

/// @brief Identity preconditioner
template <typename MatT, typename VecT>
class identity_pc : public util::preconditioner<MatT, VecT>
{
public:
    /// @brief Type of every element
    typedef typename util::preconditioner<MatT, VecT>::value_type value_type;

public:
    /// @brief Set diagonal elements
    identity_pc(const MatT &A, const value_type &omega = 1.);

    /// @brief Copy constructor
    identity_pc(const identity_pc<MatT, VecT> &jac);

    /// @brief Apply the preconditioner
    bool solve(const VecT &b, VecT &x) const;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::preconditioner<MatT, VecT>::solve;
};

/// @brief Jacobi preconditioner, i.e., scale by diagonal elements
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

/// @brief Symmetric Gauss-Seidel preconditioner, used by e.g., CG solver
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
    symmetric_gauss_seidel_pc(const MatT &A, const value_type &omega = 1.);

    /// @brief Copy constructor
    symmetric_gauss_seidel_pc(const symmetric_gauss_seidel_pc<MatT, VecT> &jac);

    /// @brief Apply the preconditioner
    bool solve(const VecT &b, VecT &x) const;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::preconditioner<MatT, VecT>::solve;
};

/// @brief Incomplete LU
template <typename MatT, typename VecT>
class ilu_pc : public util::preconditioner<MatT, VecT>
{
private:
    /// @brief matrix type must define value_type
    static_assert(la::util::has_row_idx_begin<MatT>, "MatT additionally grant access to rows");
    static_assert(la::util::has_col_idx<MatT>, "MatT additionally grant access to column indices");
    static_assert(la::util::has_nnz_access<MatT>, "MatT additionally grant access to non-zeros");
    static_assert(la::util::has_diag_idx<MatT>, "MatT additionally grant access diag_idx");

public:
    /// @brief Type of every element
    typedef typename util::preconditioner<MatT, VecT>::value_type value_type;

private:
    /// @brief L and U entries (same pattern as for A)
    VecT p_lu_values;

    /// @brief Determine L and U
    void decompose();

public:
    /// @brief Include the decompose
    ilu_pc(const MatT &A, const value_type &omega = 1.0);

    /// @brief Copy constructor
    ilu_pc(const ilu_pc<MatT, VecT> &ilu);

    /// @brief Apply the preconditioner
    bool solve(const VecT &b, VecT &x) const;

    /// @brief As we use the function name "solve" for both versions, we need to provide this
    using util::preconditioner<MatT, VecT>::solve;
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

// identity_pc
// -----------

template <typename MatT, typename VecT>
identity_pc<MatT, VecT>::identity_pc(const MatT &A,
                                     const typename identity_pc<MatT, VecT>::value_type &omega)
    : util::preconditioner<MatT, VecT>(A, omega)
{}

template <typename MatT, typename VecT>
identity_pc<MatT, VecT>::identity_pc(const identity_pc<MatT, VecT> &pc)
    : util::preconditioner<MatT, VecT>(pc.p_A, pc.p_omega)
{}

template <typename MatT, typename VecT>
bool identity_pc<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    SHAPE_ASSERT(x.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of result");
    SHAPE_ASSERT(b.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of vector");
    x = b;
    return true;
}

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

// ILU
// ---

template <typename MatT, typename VecT>
ilu_pc<MatT, VecT>::ilu_pc(const MatT &A, const value_type &omega)
    : util::preconditioner<MatT, VecT>(A, omega), p_lu_values(A.begin(), A.end())
{
    decompose();
}

template <typename MatT, typename VecT>
ilu_pc<MatT, VecT>::ilu_pc(const ilu_pc<MatT, VecT> &ilu)
    : util::preconditioner<MatT, VecT>(ilu.p_A, ilu.p_omega), p_lu_values(ilu.p_lu_values)
{}

template <typename MatT, typename VecT>
void ilu_pc<MatT, VecT>::decompose()
{
    typedef typename ilu_pc<MatT, VecT>::value_type T;
    const MatT &A = this->p_A; // Reference to avoid virtual lookups

    for (size_type i = 0; i < A.rows(); ++i) {
        // Find the diagonal element index for row i
        const size_type diag_idx = A.diag_idx(i);
        if (diag_idx == SIZE_TYPE_MAX || std::abs(p_lu_values(diag_idx) < la::util::EPS)) {
            la::util::error_factory("Zero diagonal element in ilu(0)", __FUNCTION_NAME__,
                                    la::util::NON_ZERO);
        }
        for (size_type k = A.row_idx_begin(i); k < A.row_idx_begin(i + 1); ++k) {
            const size_type j = A.col_idx(k);
            if (j < i) {                                      // Lower triangular part (L)
                p_lu_values(k) /= p_lu_values(A.diag_idx(j)); // L_ij = A_ij / U_jj

                const T l_ij = p_lu_values(k);
                // Update the rest of the row: A_ik = A_ik - L_ij * U_jk
                for (size_type kk = k + 1; kk < A.row_idx_begin(i + 1); ++kk) {
                    size_type col_k = A.col_idx(kk);
                    // Find U_jk (entry in row j with column col_k)
                    size_type u_idx = A.get_idx(j, col_k);
                    if (u_idx != SIZE_TYPE_MAX) {
                        p_lu_values(kk) -= l_ij * p_lu_values(u_idx);
                    }
                }
            }
        }
    }
}

template <typename MatT, typename VecT>
bool ilu_pc<MatT, VecT>::solve(const VecT &b, VecT &x) const
{
    SHAPE_ASSERT(b.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of result");
    SHAPE_ASSERT(x.rows() == this->p_A.rows(), "Preconditioner, invalid dimension of vector");

    typedef typename ilu_pc<MatT, VecT>::value_type T;
    const MatT &A = this->p_A; // Reference to avoid virtual lookups

    VecT y(A.rows());

    // Forward substitution: L * y = b (L has unit diagonal)
    for (size_type i = 0; i < A.rows(); ++i) {
        T sum = 0.0;
        for (size_type k = A.row_idx_begin(i); k < A.row_idx_begin(i + 1); ++k) {
            const size_type j = A.col_idx(k);
            if (j < i)
                sum += p_lu_values(k) * y(j);
            else
                break;
        }
        y(i) = b(i) - sum;
    }

    // Backward substitution: U * x = y
    for (signed_size_type i = A.rows() - 1; i >= 0; --i) {
        T sum = 0.0;
        size_type diag_idx = SIZE_TYPE_MAX;
        for (size_type k = A.row_idx_begin(i); k < A.row_idx_begin(i + 1); ++k) {
            const size_type j = A.col_idx(k);
            if ((signed_size_type)j > i)
                sum += p_lu_values(k) * x(j);
            if ((signed_size_type)j == i)
                diag_idx = k;
        }
        x(i) = (y(i) - sum) / p_lu_values(diag_idx);
    }
    return true;
}

} // namespace algorithm
} // namespace la
#endif
