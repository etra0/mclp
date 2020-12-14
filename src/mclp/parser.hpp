#include <vector>
#include <string>
#include <iostream>

class Node {
    public:
    Node(std::string nodes_filename, std::string demand_filename);

    std::vector<std::pair<int, int>> nodes;
    std::vector<int> demand;

    void print();

    private:
    void parse_file();
};