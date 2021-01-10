#include <cstring>
#include <iostream>
#include <mclp/argparse.hpp>
#include <mclp/base_structure.hpp>
#include <mclp/solver.hpp>
#include <memory>
#include <stdexcept>

int main(const int argc, const char *argv[]) {
  mclp::arguments args{};

  try {
    if (!args.parse(argc, argv))
      return EXIT_SUCCESS;
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  mclp::domain d;
  try {
    d.parse_files(args.nodes, args.demand);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  mclp::solver s(d, args.p, args.S);

#ifdef RANDOM_SOL
  s.find_random_solution();
#else
  s.find_initial_solution();
#endif

  std::cout << "Initial solution:" << std::endl;
  s.print();

#ifdef SAVE_SOLUTIONS
  s.save_solution("solutions/solution_0000");
#endif

  char buffer[100];
  std::memset(buffer, 0, sizeof(char));
  for (uint32_t i = 1; i < args.it; i++) {
    if (!s.refine_solution())
      break;
#ifdef SAVE_SOLUTIONS
    sprintf(buffer, "solutions/solution_%04d", i);
    s.save_solution(buffer);
#endif
  }

  s.save_solution();

  std::cout << "Best solution:" << std::endl;
  s.print();

  return EXIT_SUCCESS;
}
