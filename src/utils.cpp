#include <mclp/utils.hpp>

int utils::eucl_distance(Node const &a, Node const &b) {
  auto x = a.x - b.x;
  auto y = a.y - b.y;
  return static_cast<int>(std::sqrt(x * x + y * y));
}

utils::Benchmark::Benchmark(const char *name_) : name(name_), start() {
  start = std::chrono::high_resolution_clock::now();
}

utils::Benchmark::~Benchmark() {
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();
  std::cout << "Time elapsed in " << name << ": " << elapsed << "ms"
            << std::endl;
}
