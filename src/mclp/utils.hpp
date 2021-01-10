/* Utils contains some useful functions that are not tightly related to the
 * algorithm.
 */

#include <chrono>
#include <cmath>
#include <iostream>
#include <mclp/base_structure.hpp>
#include <utility>

#ifndef MCLP_MCLP_UTILS_H_
#define MCLP_MCLP_UTILS_H_


namespace mclp {

namespace utils {
uint32_t eucl_distance(node const &a, node const &b);

// Class useful to do some basic benchmarking when doing the testing. It's
// scope sensitive.
class benchmark {
public:
  std::string name;
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  benchmark(const char *name);
  benchmark() : name("unknown"), start(){};
  ~benchmark();
};

} // namespace utils

} // namespace mclp

#endif // MCLP_MCLP_UTILS_H_
