#include <mclp/parser.hpp>

Node::Node(std::string nodes_filename, std::string demand_filename) {
    this->parse_file();
}

void Node::parse_file() {
    std::cout << "Hello world from parsing!" << std::endl;
}