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

/// @brief Check if two triplets storing the same non-zero by row and column index
template <typename T>
inline bool operator==(const triplet<T> &left, const triplet<T> &right)
{
    return left.row == right.row && left.col == right.col;
}

/// @brief Check if a triplet is "smaller" than another
template <typename T>
inline bool operator<(const triplet<T> &left, const triplet<T> &right)
{
    if (left.row < right.row) {
        return true;
    }
    if (left.row == right.row) {
        return left.col < right.col;
    }
    return false;
}

/// @brief Check if two triplets storing the same non-zero by row and column index
template <typename T>
inline bool operator<=(const triplet<T> &left, const triplet<T> &right)
{
    return left < right || left == right;
}

} // namespace util

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

    /// @brief Compress the values according to the assembly strategy
    /// @pre values are sorted!
    void compress_sorted();

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
        p_vals.begin(), p_vals.end());
}

template <typename T, util::AssembleStrategy assemble_strategy>
void triplet_sparse_matrix<T, assemble_strategy>::compress_sorted()
{
    if (!p_vals.empty()) {
        size_type dest = 0;
        for (size_type src = 1; src < p_vals.size(); ++src) {
            if (p_vals[src] == p_vals[dest]) {
                if constexpr (assemble_strategy == util::OVERWRITE) {
                    p_vals[dest].value = p_vals[src].value;
                } else { // SUM
                    p_vals[dest].value += p_vals[src].value;
                }
            } else {
                ++dest;
                if (dest != src) {
                    p_vals[dest] = p_vals[src];
                }
            }
            BOUNDARY_ASSERT(p_vals[dest] <= p_vals[src], "values are not sorted");
        }
        p_vals.resize(dest + 1);
    }
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
    LOG_INFO("Building spare matrix from triplets");
    sort_vals();
    compress_sorted();

    LOG_DEBUG("Assemble sparse matrix from " << p_vals.size() << " triplets");
    // Allocate memory for the sparse matrix
    sparse_matrix<T> A;
    A.allocate(p_rows, p_cols, p_vals.size());

    size_type *row_ptr = A.begin_row_ptr();
    size_type *col_idx = A.begin_col_idx();
    T *val_ptr = A.begin();

    row_ptr[0] = 0;
    size_type current_row = 0;
    for (size_type i = 0; i < p_vals.size(); ++i) {
        const auto &trip = p_vals[i];

        // Fill row pointers for jumps to next row(s)
        while (current_row < trip.row) {
            row_ptr[++current_row] = i;
        }

        col_idx[i] = trip.col;
        val_ptr[i] = trip.value;
    }
    // Fill remaining row pointers
    while (current_row < p_rows) {
        row_ptr[++current_row] = p_vals.size();
    }
    LOG_INFO("Created sparse matrix");
    return A;
}

} // namespace la
#endif
