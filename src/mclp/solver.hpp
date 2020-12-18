#include <mclp/base_structure.hpp>
#include <mclp/utils.hpp>
#include <set>

#ifndef MCLP_MCLP_SOLVER_H_
#define MCLP_MCLP_SOLVER_H_

class Solver {
public:
  Domain domain;
  std::vector<Node> best_solution;

  int p;
  int S;

  Solver(Domain domain_, int p_, int S_)
      : domain(domain_), best_solution(), p(p_), S(S_){};

  // Do a greedy search of a initial solution.
  void find_initial_solution();

  void print();
  void save_solution();
};

#endif // MCLP_MCLP_SOLVER_H_
