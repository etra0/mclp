#include <mclp/parser.hpp>

void Node::print() {
  std::cout << "{ x: " << x << ", y: " << y << ", demand: " << demand << " }\n";
}

void Domain::parse_files(std::string nodes_filename,
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

  for (uint32_t i = 0; i < N; i++) {
    int x, y;
    uint32_t demand;
    nodes_file >> x;
    nodes_file >> y;
    demand_file >> demand;
    this->nodes.emplace_back(x, y, demand);
  }
}

void Domain::print() {
  std::cout << "Nodes:" << std::endl;
  for (auto t : this->nodes) {
    t.print();
  }
}
