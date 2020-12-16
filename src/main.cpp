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

  Node n;
  try {
    n.parse_files(args->nodes, args->demand);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  Solver s(n, args->p, args->S);

  s.find_initial_solution();

  return EXIT_SUCCESS;
}
