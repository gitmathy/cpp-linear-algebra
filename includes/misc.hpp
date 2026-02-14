#ifndef LA_MISC_H
#define LA_MISC_H

#include <cstdlib>

namespace la
{

template <typename T> inline double get_random() { return T((std::rand() / (T)RAND_MAX) * 2 - 1); }

} // namespace la
#endif
