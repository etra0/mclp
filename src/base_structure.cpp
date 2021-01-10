#include <mclp/base_structure.hpp>

namespace mclp {

void node::print() const {
  std::cout << "{ x: " << x << ", y: " << y << ", demand: " << demand << " }\n";
}

void domain::parse_files(std::string nodes_filename,
                         std::string demand_filename) {
  std::ifstream nodes_file;
  std::ifstream demand_file;

  nodes_file.open(nodes_filename);
  if (!nodes_file.is_open()) {
    std::string errmsg = "Can't open the node file " + nodes_filename;
    throw std::invalid_argument(errmsg);
  }

  demand_file.open(demand_filename, std::ios::in | std::ifstream::binary);
  if (!demand_file.is_open()) {
    std::string errmsg = "Can't open the demand file " + demand_filename;
    throw std::invalid_argument(errmsg);
  }

  uint32_t N;

  // First read the number of pairs.
  nodes_file >> N;

  if (N <= 0) {
    throw std::invalid_argument("N must be greater than 0");
  }

  for (uint32_t i = 0; i < N; i++) {
    int x, y;
    uint32_t demand;
    nodes_file >> x;
    nodes_file >> y;
    demand_file >> demand;
    this->nodes.emplace_back(x, y, demand);
  }
  this->calculate_all_demand();
}

void domain::print() {
  std::cout << "Nodes:" << std::endl;
  for (auto t : this->nodes) {
    t.print();
  }

}

void domain::calculate_all_demand() {
  sum_demand = 0;
  for (auto &n : nodes) {
    sum_demand += n.demand;
  }
}

} // namespace mclp
