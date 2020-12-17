#include <mclp/parser.hpp>
#include <mclp/utils.hpp>
#include <set>

class Solver {
public:
  Domain domain;
  std::vector<Node> best_solution;

  int p;
  int S;

  Solver(Domain domain_, int p_, int S_)
      : domain(domain_), best_solution(), p(p_), S(S_){};

  void print();
  void find_initial_solution();
};
