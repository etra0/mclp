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
  void print() const;

  friend inline bool operator==(const node &curr, const node &other) {
    return curr.x == other.x && curr.y == other.y &&
           curr.demand == other.demand;
  }

  friend inline bool operator!=(const node &curr, const node &other) {
    return !(curr == other);
  }
};

class domain {
public:
  std::vector<node> nodes;
  uint32_t sum_demand;

  domain() : nodes(), sum_demand(0) {};

  void print();
  void parse_files(std::string nodes_filename, std::string demand_filename);

private:
  void calculate_all_demand();
};

} // namespace mclp

#endif // MCLP_MCLP_BASE_STRUCTURE_H_
