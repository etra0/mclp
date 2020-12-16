#include <mclp/parser.hpp>
#include <set>

class Solver {
	public:
	Node domain;
	std::vector<coord> best_solution;

    int p;
    int S;

	Solver(Node domain_, int p_, int S_) : domain(domain_), best_solution(), p(p_), S(S_) {};

	void print();
	void find_initial_solution();
};
