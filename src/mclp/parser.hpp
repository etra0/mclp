#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <iterator>

class Node {
    public:
    std::vector<std::pair<int, int>> nodes;
    std::vector<int> demand;

    Node(): nodes(), demand() {};

    void print();

    void parse_files(std::string nodes_filename, std::string demand_filename);
};