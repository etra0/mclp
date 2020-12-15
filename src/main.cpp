#include <iostream>
#include <mclp/parser.hpp>
#include <stdexcept>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Incorrect arguments" << std::endl;
    return EXIT_FAILURE;
  }

  std::string nodes = argv[1];
  std::string demand = argv[2];

  Node n;
  try {
    n.parse_files(nodes, demand);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  n.print();

  return EXIT_SUCCESS;
}