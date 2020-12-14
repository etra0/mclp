#include <mclp/parser.hpp>

Node::Node() {
    nodes = std::vector<std::pair<int, int>>();
    demand = std::vector<int>();
}

void Node::parse_files(std::string nodes_filename, std::string demand_filename) {
    std::ifstream nodes;
    std::ifstream demand;

    nodes.open(nodes_filename);
    if (!nodes.is_open()) {
        std::string errmsg = "Can't open the node file " + nodes_filename;
        throw std::invalid_argument(errmsg);
    }

    demand.open(demand_filename, std::ios::in | std::ifstream::binary);
    if (!demand.is_open()) {
        std::string errmsg = "Can't open the demand file " + demand_filename;
        throw std::invalid_argument(errmsg);
    }

    uint32_t N;

    // First read the number of pairs.
    nodes >> N;
    for (uint32_t i = 0; i < N; i++) {
        int a, b;
        nodes >> a;
        nodes >> b;
        this->nodes.push_back(std::pair<int, int>(a, b));
    }

    std::istream_iterator<int> iter(demand);
    std::copy(iter, std::istream_iterator<int>(), std::back_inserter(this->demand));
    if (this->demand.size() != N) {
        throw std::invalid_argument("There number of elements in node doesn't match with demand");
    }
}

void Node::print() {
    std::cout << "Nodes:" << std::endl;
    for (auto t : this->nodes) {
        std::cout << t.first << " " << t.second << std::endl;
    }

    std::cout << "Demand:" << std::endl;
    for (auto t: this->demand) {
        std::cout << t << std::endl;
    }
}