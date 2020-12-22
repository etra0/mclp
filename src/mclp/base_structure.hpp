#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef MCLP_MCLP_BASE_STRUCTURE_H_
#define MCLP_MCLP_BASE_STRUCTURE_H_

namespace mclp {

class node {
public:
  int x;
  int y;
  uint32_t demand;

  node(int x, int y, uint32_t demand) : x(x), y(y), demand(demand){};
  void print();
};

class domain {
public:
  std::vector<node> nodes;

  domain() : nodes(){};

  void print();
  void parse_files(std::string nodes_filename, std::string demand_filename);
};

} // namespace mclp

#endif // MCLP_MCLP_BASE_STRUCTURE_H_
