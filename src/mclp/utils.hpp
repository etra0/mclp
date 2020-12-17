#include <cmath>
#include <mclp/base_structure.hpp>
#include <utility>
#include <iostream>
#include <chrono>

namespace utils {
int eucl_distance(Node const &a, Node const &b);

// Class useful to do some basic benchmarking when doing the testing. It's
// scope sensitive.
class Benchmark {
    public:
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    Benchmark(const char *name_);
    Benchmark() : name("unknown"){};
    ~Benchmark();
};
}

