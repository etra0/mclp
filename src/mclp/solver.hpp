#include <mclp/parser.hpp>

class Solver {
	public:
	Solver(Node domain) : domain(domain) {};
	Node domain;
	std::vector<coord> best_solution;

	void print();
	void find_initial_solution();
};
