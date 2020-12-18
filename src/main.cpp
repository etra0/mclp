#include <iostream>
#include <mclp/argparse.hpp>
#include <mclp/base_structure.hpp>
#include <mclp/solver.hpp>
#include <memory>
#include <stdexcept>

int main(const int argc, const char *argv[]) {
  Arguments args{};

  try {
    if (!args.parse(argc, argv))
      return EXIT_SUCCESS;
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  Domain d;
  try {
    d.parse_files(args.nodes, args.demand);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  Solver s(d, args.p, args.S);

  s.find_initial_solution();

  s.print();

  s.save_solution();

  return EXIT_SUCCESS;
}
