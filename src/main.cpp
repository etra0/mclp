#include <iostream>
#include <mclp/parser.hpp>
#include <mclp/solver.hpp>
#include <mclp/argparse.hpp>
#include <stdexcept>
#include <memory>


int main(const int argc, const char *argv[]) {
	std::unique_ptr<Arguments> args;

	try {
		args = std::make_unique<Arguments>(argc, argv);
	} catch (std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
	}

  Node n;
  try {
    n.parse_files(args->nodes, args->demand);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  Solver s(n);

  s.find_initial_solution();

  return EXIT_SUCCESS;
}
