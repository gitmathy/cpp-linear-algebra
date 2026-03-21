/// Part of the project "cpp-linear-algebra"
///
/// @file la/data_structure/triplet_sparse_matrix.hpp
/// @brief Declaration and definition of a sparse matrix class builder
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_DATA_STRUCTURE_TRIPLET_SPARSE_MATRIX_HPP
#define LA_DATA_STRUCTURE_TRIPLET_SPARSE_MATRIX_HPP

#include "la/data_structure/forward.hpp"
#include "la/util/constants.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

namespace la {

namespace util {

/// @brief storing one non-zero in the triplet sparse matrix
template <typename T>
struct triplet
{
    size_type row;
    size_type col;
    T value;
};

/// @brief Assemble strategy
enum AssembleStrategy {
    SUM,      // sum all non-zeros with same row and column index
    OVERWRITE // last non-zero overwrite previous ones
};

} // namespace util

/// @brief Check if two triplets storing the same non-zero by row and column index
template <typename T>
inline bool operator==(const util::triplet<T> &a, const util::triplet<T> &b)
{
    return a.row == b.row && a.col == b.col;
}

/// @brief Build a matrix by storing triplets.
///
/// This type of spare matrix is optimized for writing non-zeros via the operator ()(i,j). This has
/// a complexity of O(1). Reading an element has complexity of O(n). Assembling the matrix includes
/// a sorting and is of O(n log(n)).
template <typename T, util::AssembleStrategy assemble_strategy = util::OVERWRITE>
class triplet_sparse_matrix
{
public:
    /// @brief Type of every element
    typedef T value_type;

private:
    /// @brief All non-zero elements are stored as triplets
    std::vector<util::triplet<T>> p_vals;

    /// @brief Number of rows
    size_type p_rows;

    /// @brief Number of columns
    size_type p_cols;

    /// @brief Sort by row, then by col
    void sort_vals();

public:
    /// @brief Construct with given number of rows and columns
    explicit triplet_sparse_matrix(const size_type rows, const size_type cols,
                                   const size_type expected_nnz = 0);

    /// @brief Default destructor
    ~triplet_sparse_matrix() = default;

    /// @brief Set dimensions (and clear everything)
    void allocate(const size_type rows, const size_type cols, const size_type expected_nnz = 0);

    /// @brief write access to an element
    inline T &operator()(const size_type i, const size_type j);

    /// @brief read access to an element
    inline const T operator()(const size_type i, const size_type j) const;

    /// @brief Number of rows
    inline size_type rows() const { return p_rows; }

    /// @brief Number of columns
    inline size_type cols() const { return p_cols; }

    /// @brief Build the sparse matrix  (while keeping all elements in the builder)
    sparse_matrix<T> assemble();
};

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

template <typename T, util::AssembleStrategy assemble_strategy>
void triplet_sparse_matrix<T, assemble_strategy>::sort_vals()
{
    std::stable_sort(
#ifdef PARALLEL
        execution::par_unseq,
#endif
        p_vals.begin(), p_vals.end(), [](const auto &left, const auto &right) {
            if (left.row < right.row) {
                return true;
            }
            if (left.row == right.row) {
                return left.col < right.col;
            }
            return false;
        });
}

template <typename T, util::AssembleStrategy assemble_strategy>
triplet_sparse_matrix<T, assemble_strategy>::triplet_sparse_matrix(const size_type rows,
                                                                   const size_type cols,
                                                                   const size_type expected_nnz)
    : p_vals(0), p_rows(0), p_cols(0)
{
    allocate(rows, cols, expected_nnz);
}

template <typename T, util::AssembleStrategy assemble_strategy>
void triplet_sparse_matrix<T, assemble_strategy>::allocate(const size_type rows,
                                                           const size_type cols,
                                                           const size_type expected_nnz)
{
    p_vals.resize(0); // clean everything
    if (expected_nnz > 0) {
        p_vals.reserve(expected_nnz);
    }
    p_cols = cols;
    p_rows = rows;
}

template <typename T, util::AssembleStrategy assemble_strategy>
inline T &triplet_sparse_matrix<T, assemble_strategy>::operator()(const size_type i,
                                                                  const size_type j)
{
    LOG_TRACE("triplet_sparse_matrix: Write access to element " << i << ", " << j);
    BOUNDARY_ASSERT(i < rows() && j < cols(), "triplet_sparse_matrix: out of bound");
    p_vals.emplace_back(i, j, T(0));
    return p_vals.back().value;
}

template <typename T, util::AssembleStrategy assemble_strategy>
inline const T triplet_sparse_matrix<T, assemble_strategy>::operator()(const size_type i,
                                                                       const size_type j) const
{
    LOG_TRACE("triplet_sparse_matrix: Read access to element " << i << ", " << j);
    if constexpr (assemble_strategy == util::OVERWRITE) {
        // As we don't have a particular order, we search the most last added element
        auto it = std::find_if(p_vals.crbegin(), p_vals.crend(),
                               [i, j](const auto &x) { return i == x.row && j == x.col; });
        return it == p_vals.crend() ? T(0) : it->value;
    } else { // SUM
        return std::accumulate(p_vals.cbegin(), p_vals.cend(), T(0), [i, j](T acc, const auto &x) {
            if (x.row == i && x.col == j) {
                return acc + x.value;
            }
            return acc;
        });
    }
}

template <typename T, util::AssembleStrategy assemble_strategy>
sparse_matrix<T> triplet_sparse_matrix<T, assemble_strategy>::assemble()
{
    sort_vals();
    // Preassemble to perform assemble strategy amd get number of non-zeros
    size_type unique_nz = 0, nnz = 0;
    const size_type size = p_vals.size();
    for (size_type i = 0; i < size; ++i) {
        if (i > 0 && p_vals[i] == p_vals[unique_nz]) {
            // the next element has the size row and col index, apply strategy
            if constexpr (assemble_strategy == util::OVERWRITE) {
                p_vals[unique_nz].value = p_vals[i].value;
            } else { // SUM
                p_vals[unique_nz].value += p_vals[i].value;
            }
        } else { // next element has another row and column index
            unique_nz = i;
            ++nnz;
        }
    }
    // Allocate memory for the sparse matrix
    sparse_matrix<T> A;
    A.allocate(p_rows, p_cols, nnz);
    size_type last_row_idx = 0, last_col_idx = SIZE_TYPE_MAX; // last row and column index
    size_type nnz_idx = 0;                                    // index of curent non-zero
    size_type row_elements = 0;                               // number of elements in current row
    size_type *row_ptr = A.begin_row_ptr();                   // access to row_ptr
    size_type *col_idx = A.begin_col_idx();                   // access to col_idx
    T *val_ptr = A.begin();                                   // access to values;

    row_ptr[0] = 0;
    for (size_type i = 0; i < p_vals.size(); ++i) {
        const util::triplet<T> &val = p_vals[i];
        LOG_DEBUG("Include element " << val.row << ", " << val.col << " in matrix");
        if (val.row > last_row_idx) {
            // we are in a next row
            for (size_type row_offset = 1; row_offset <= val.row - last_row_idx; ++row_offset) {
                LOG_TRACE("Setting row_ptr[" << last_row_idx + row_offset << ": "
                                             << row_ptr[last_row_idx] + row_elements);
                row_ptr[last_row_idx + row_offset] = row_ptr[last_row_idx] + row_elements;
            }
            row_elements = 0;
            last_row_idx = val.row;
        } else if (val.col == last_col_idx) {
            // As the values have been sorted, we only consider the first one due to preassemble.
            LOG_TRACE("Skipping element " << val.row << ", " << val.col);
            continue;
        }
        // Same row but new column index
        col_idx[nnz_idx] = val.col;
        val_ptr[nnz_idx] = val.value;

        // move on
        ++nnz_idx;
        ++row_elements;
        last_col_idx = val.col;
    }
    row_ptr[last_row_idx] = nnz_idx - row_elements;
    for (size_type i = last_row_idx; i < p_rows; ++i)
    {
        row_ptr[i+1] = nnz_idx;
    }

    return A;
}

} // namespace la
#endif
