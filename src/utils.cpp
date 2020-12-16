#include <mclp/utils.hpp>

int utils::eucl_distance(std::pair<int, int> const & a, std::pair<int, int> const & b) {
    auto x = a.first  - b.first;
    auto y = a.second - b.second;
    return static_cast<int>(std::sqrt(x*x + y*y));
}
