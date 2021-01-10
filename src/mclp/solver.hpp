#include <algorithm>
#include <deque>
#include <mclp/base_structure.hpp>
#include <mclp/utils.hpp>
#include <random>
#include <set>
#include <iomanip>

#ifndef MCLP_MCLP_SOLVER_H_
#define MCLP_MCLP_SOLVER_H_

#ifndef SEED
#define SEED 1234
#endif

#ifndef TABU_SIZE
#define TABU_SIZE 200
#endif

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
  // We need to keep track of the best score in order to check if the new
  // solution is better than the actual one.
  uint32_t best_score;

  // We must save the best solution overall so these variables are the best
  // solution found within all iterations
  std::vector<node> global_best_solution;
  uint32_t global_best_score;

  // Parameters of the problem.
  // * p: number of servers
  // * S: radius that a server will cover.
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

  // Do a random assignment for the initial solution
  void find_random_solution();

  // Use tabu search to refine solution in order to find a more optimal one.
  int refine_solution();

  // Extra helper functions
  void print();
  // Save solution with a name will save the current sol (not global sol)
  void save_solution(std::string name);

  // This will save the global solution
  void save_solution();

private:
  // We use this function to calculate the score for a solution candidate.
  uint32_t calculate_score(std::vector<node> &current_sol);
};

} // namespace mclp
#endif // MCLP_MCLP_SOLVER_H_
