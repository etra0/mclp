#include <iostream>
#include <mclp/argparse.hpp>
#include <mclp/parser.hpp>
#include <mclp/solver.hpp>
#include <memory>
#include <stdexcept>

int main(const int argc, const char *argv[]) {
  std::unique_ptr<Arguments> args;

  try {
    args = std::make_unique<Arguments>(argc, argv);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  Domain d;
  try {
    d.parse_files(args->nodes, args->demand);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  Solver s(d, args->p, args->S);

  s.find_initial_solution();

  s.print();

  return EXIT_SUCCESS;
}
