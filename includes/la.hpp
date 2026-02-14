#ifndef LA_LA_H
#define LA_LA_H

#include "includes/types.hpp"
#include "includes/vector.hpp"

namespace la
{

/// ===============================================
/// A D D I T I O N
/// ===============================================

template <typename T> vector<T> operator+(const vector<T> &left, const vector<T> right);

/// ===============================================
/// T E M P L A T E   I M P L E M E N T A T I O N S
/// ===============================================

template <typename T> vector<T> operator+(const vector<T> &left, const vector<T> right)
{
    vector<T> result(left);
    return result += right;
}

} // namespace la
#endif
