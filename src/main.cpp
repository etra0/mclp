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

  s.find_initial_solution();

  s.print();

  s.save_solution("solutions/solution_0000");

  char buffer[100];
  std::memset(buffer, 0, sizeof(char));
  for (uint32_t i = 1; i < args.it; i++) {
    if (!s.refine_solution())
      break;
    sprintf(buffer, "solutions/solution_%04d", i);
    s.save_solution(buffer);
  }

  s.save_solution();

  return EXIT_SUCCESS;
}
