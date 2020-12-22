#include <mclp/utils.hpp>

namespace mclp {

uint32_t utils::eucl_distance(node const &a, node const &b) {
  auto x = a.x - b.x;
  auto y = a.y - b.y;
  return static_cast<uint32_t>(std::sqrt(x * x + y * y));
}

utils::benchmark::benchmark(const char *name) : name(name), start() {
  start = std::chrono::high_resolution_clock::now();
}

utils::benchmark::~benchmark() {
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();
  std::cout << "Time elapsed in `" << name << "`: " << elapsed << "ms"
            << std::endl;
}

} // namespace mclp
