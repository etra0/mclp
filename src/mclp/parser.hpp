#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <iterator>

#pragma once

typedef std::pair<int, int> coord;

class Node {
    public:
    std::vector<coord> nodes;
    std::vector<int> demand;

    Node(): nodes(), demand() {};

    void print();

    void parse_files(std::string nodes_filename, std::string demand_filename);
};
