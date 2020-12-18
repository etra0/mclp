#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef MCLP_MCLP_BASE_STRUCTURE_H_
#define MCLP_MCLP_BASE_STRUCTURE_H_

class Node {
public:
  int x;
  int y;
  uint32_t demand;

  Node(int x_, int y_, uint32_t demand_) : x(x_), y(y_), demand(demand_){};
  void print();
};

class Domain {
public:
  std::vector<Node> nodes;

  Domain() : nodes(){};

  void print();
  void parse_files(std::string nodes_filename, std::string demand_filename);
};

#endif // MCLP_MCLP_BASE_STRUCTURE_H_
