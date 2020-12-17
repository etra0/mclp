#include <mclp/utils.hpp>

int utils::eucl_distance(Node const &a, Node const &b) {
  auto x = a.x - b.x;
  auto y = a.y - b.y;
  return static_cast<int>(std::sqrt(x * x + y * y));
}
