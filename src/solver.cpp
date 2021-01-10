#include <mclp/solver.hpp>

namespace mclp {

void solver::print() {

  std::cout.precision(3);
  std::cout << "Score: " << global_best_score << std::endl;
  std::cout << "Total coverage: " << global_best_score*100. / problem_domain.sum_demand << "%" << std::endl;
  for (auto n : global_best_solution) {
    n.print();
  }
}

void solver::save_solution(std::string name) {
  std::ofstream out;

  out.open(name, std::ofstream::trunc);

  out << best_score << std::endl;
  out << S << std::endl;
  for (auto n : best_solution) {
    out << n.x << " " << n.y << std::endl;
  }
}

void solver::save_solution() {
  std::ofstream out;

  out.open("best_solution", std::ofstream::trunc);

  out << best_score << std::endl;
  out << S << std::endl;
  for (auto n : best_solution) {
    out << n.x << " " << n.y << std::endl;
  }
}

void solver::find_random_solution() {
  std::mt19937 gen(SEED);
  auto &domain_nodes = problem_domain.nodes;
  auto size = static_cast<int>(domain_nodes.size());
  std::uniform_int_distribution<> distrib(0, size);

  for (uint32_t i = 0; i < p; i++) {
    auto v = static_cast<size_t>(distrib(gen));
    best_solution.push_back(domain_nodes[v]);
  }

  best_score = calculate_score(best_solution);
  global_best_solution = best_solution;
  global_best_score = best_score;
}

void solver::find_initial_solution() {
  utils::benchmark b(__PRETTY_FUNCTION__);

  // Do a deep copy to avoid some UB.
  auto const nodes = std::vector<node>(this->problem_domain.nodes);
  auto n_facilities = this->p;
  std::cout << "Calculating initial solution with:"
               "\np:\t\t"
            << n_facilities << "\nS:\t\t" << S << "\nn_nodes:\t" << nodes.size()
            << std::endl;

  // initial_sol will contain the index of
  std::set<uint32_t> initial_sol{};

  // We shouldn't lookup for already covered cases to avoid some repetition
  std::set<size_t> covered_cases{};

  // current_covered_cases are the covered cases per iteration
  std::set<size_t> current_covered_cases{};

  // The best_current_covered_cases are the cases covered by the best
  // iteration, similar to best_case_p and best_case_counter
  std::set<size_t> best_current_covered_cases{};

  while (n_facilities--) {
    uint32_t best_case_p = 0;
    uint32_t best_case_counter = 0;

    for (size_t i = 0; i < nodes.size(); i++) {
      // Skip nodes already covered
      // if (covered_cases.find(i) != covered_cases.end())
      //   continue;
      auto const &origin = nodes[i];

      current_covered_cases.clear();

      uint32_t counter = 0;

      for (size_t j = 0; j < nodes.size(); j++) {
        if (covered_cases.find(j) != covered_cases.end())
          continue;
        auto const &destination = nodes[j];

        auto distance = utils::eucl_distance(origin, destination);
        if (distance <= S) {
          counter += destination.demand;
          current_covered_cases.insert(j);
        }
      }

      if (counter > best_case_counter &&
          initial_sol.find(static_cast<uint32_t>(i)) == initial_sol.end()) {
        best_case_counter = counter;
        best_current_covered_cases = current_covered_cases;
        best_case_p = static_cast<uint32_t>(i);
      }
    }

    initial_sol.insert(best_case_p);
    covered_cases.merge(best_current_covered_cases);
    best_score += best_case_counter;
  }

  std::vector<node> current_sol{};
  for (auto v : initial_sol) {
    current_sol.push_back(nodes[v]);
  }

  best_solution = current_sol;
  global_best_solution = current_sol;
  global_best_score = best_score;
}

int solver::refine_solution() {
  auto const &current_sol = best_solution;
  uint32_t current_best_score = 0;

  std::pair<size_t, size_t> candidate{0, 0};

  for (size_t i = 0; i < current_sol.size(); i++) {
    auto &node = current_sol[i];

    for (size_t j = 0; j < problem_domain.nodes.size(); j++) {
      if (i == j)
        continue;
      auto const &destination = problem_domain.nodes[j];
      if (node == destination)
        continue;

      // Check for candidates to the new solution
      if (mclp::utils::eucl_distance(node, destination) <= S) {

        // We copy the current best solution and then replace the current node
        // to calculate the new score, if the new score is bigger than the
        // current best score, is replaced and the candidate is saved.
        auto current_sol_ = current_sol;
        current_sol_[i] = destination;
        auto current_score = solver::calculate_score(current_sol_);

        // Check if the current index is in the tabu list.
        auto in_tabu = std::find(tabulist.begin(), tabulist.end(),
                                 destination) != tabulist.end();
        if (current_score > current_best_score && !in_tabu) {
          current_best_score = current_score;
          candidate.first = i;
          candidate.second = j;
        }
      }
    }
  }

  if (candidate.first == 0 && candidate.second == 0) {
    std::cout << "Couldn't found a better solution, stopping further iterations"
              << std::endl;
    return 0;
  }

  tabulist.push_back(best_solution[candidate.first]);

  // We check if the tabu list exceeds the allowed size and since it's a queue
  // we can remove the front easily.
  if (tabulist.size() > TABU_SIZE) {
    tabulist.pop_front();
  }

  best_solution[candidate.first] = problem_domain.nodes[candidate.second];
  best_score = current_best_score;

  if (best_score > global_best_score) {
    global_best_score = best_score;
    global_best_solution = best_solution;
  }

  return 1;
}

uint32_t solver::calculate_score(std::vector<node> &current_sol) {
  std::set<uint32_t> covered_cases;
  uint32_t score = 0;
  auto &domain = problem_domain.nodes;

  for (auto &destination : domain) {
    for (auto &sol : current_sol) {
      if (mclp::utils::eucl_distance(destination, sol) <= S) {
        score += destination.demand;
        break;
      }
    }
  }

  return score;
}

} // namespace mclp
