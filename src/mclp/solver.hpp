#include <algorithm>
#include <deque>
#include <mclp/base_structure.hpp>
#include <mclp/utils.hpp>
#include <random>
#include <set>

#ifndef MCLP_MCLP_SOLVER_H_
#define MCLP_MCLP_SOLVER_H_

#define TABU_SIZE 200

namespace mclp {

class solver {
public:
  // Domain is a basic class that contains the basic information of the problem
  // set.
  domain problem_domain;

  // Vector containing the current best solution, which we mutate every time we
  // need to do a new iteration of the tabu list. We populate this list for the
  // first time when we do the Greedy search.
  std::vector<node> best_solution;
  uint32_t best_score;

  std::vector<node> global_best_solution;
  uint32_t global_best_score;

  // We need to keep track of the best score in order to check if the new
  // solution is better than the actual one.

  uint32_t p;
  uint32_t S;

  // We use deque since we need to have iterators to be able to check if the
  // values are inside the queue already (We can't iterate over std::queue).
  std::deque<node> tabulist;

  solver(domain d, uint32_t p, uint32_t S)
      : problem_domain(d), best_solution(), best_score(0), p(p), S(S),
        global_best_solution(), global_best_score(0){};

  // Do a greedy search of a initial solution.
  void find_initial_solution();

  // Do a random assignment of solution
  void find_random_solution();

  // Use tabu search to refine solution in order to find a more optimal one.
  int refine_solution();

  void print();
  void save_solution(std::string name);
  void save_solution();

private:
  uint32_t calculate_score(std::vector<node> &current_sol);
};

} // namespace mclp
#endif // MCLP_MCLP_SOLVER_H_
