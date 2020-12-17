#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

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
