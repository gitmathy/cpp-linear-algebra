#include "tests/includes/samples.hpp"

namespace la {
namespace test {

std::shared_ptr<sample_la_structures<double>>
get_default_samples(size_type vec_rows, size_type mat_rows, size_type mat_cols)
{
    static std::shared_ptr<sample_la_structures<double>> defaults(nullptr);
    if (defaults == nullptr) {
        defaults = std::make_shared<sample_la_structures<double>>(vec_rows, mat_rows, mat_cols);
    }
    return defaults;
}

} // namespace test
} // namespace la
