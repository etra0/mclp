#include <algorithm>
#include <deque>
#include <mclp/base_structure.hpp>
#include <mclp/utils.hpp>
#include <set>

#ifndef MCLP_MCLP_SOLVER_H_
#define MCLP_MCLP_SOLVER_H_

#define TABU_SIZE 10

namespace mclp {

class solver {
public:
  domain problem_domain;
  std::vector<node> best_solution;
  uint32_t best_score;

  uint32_t p;
  uint32_t S;
  std::deque<size_t> tabulist;

  solver(domain d, uint32_t p, uint32_t S)
      : problem_domain(d), best_solution(), best_score(0), p(p), S(S){};

  // Do a greedy search of a initial solution.
  void find_initial_solution();

  // Use tabu search to refine solution in order to find a more optimal one.
  void refine_solution();

  void print();
  void save_solution(std::string name);

private:
  uint32_t calculate_score(std::vector<node> current_sol);
};

} // namespace mclp
#endif // MCLP_MCLP_SOLVER_H_
