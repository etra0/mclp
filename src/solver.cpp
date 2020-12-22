#include <mclp/solver.hpp>

void Solver::print() {
  for (auto n : best_solution) {
    n.print();
  }
}

// TODO: delet this
void Solver::save_solution() {
  std::ofstream out;

  out.open("solution");

  out << S << std::endl;
  for (auto n : best_solution) {
    out << n.x << " " << n.y << std::endl;
  }
}

void Solver::find_initial_solution() {
  utils::Benchmark b(__PRETTY_FUNCTION__);
  // Do a deep copy to avoid some UB.
  auto nodes = std::vector<Node>(this->domain.nodes);
  auto loop_counter = this->p;
  std::cout << "Calculating initial solution with:" \
    "\np:\t\t" << loop_counter << \
    "\nS:\t\t" << S << \
    "\nn_nodes:\t" << nodes.size() << std::endl;

  // initial_sol will contain the index of 
  std::set<uint32_t> initial_sol{};

  // We shouldn't lookup for already covered cases to avoid some repetition
  std::set<size_t> covered_cases{};

  // current_covered_cases are the covered cases per iteration
  std::set<size_t> current_covered_cases{};

  // The best_current_covered_cases are the cases covered by the best
  // iteration, similar to best_case_p and best_case_counter
  std::set<size_t> best_current_covered_cases{};


  while (loop_counter--) {
    uint32_t best_case_p = 0;
    uint32_t best_case_counter = 0;

    for (size_t i = 0; i < nodes.size(); i++) {
      // Skip nodes already covered
      if (covered_cases.find(i) != covered_cases.end())
        continue;
      auto const& origin = nodes[i];

      current_covered_cases.clear();

      uint32_t counter = 0;

      for (size_t j = 0; j < nodes.size(); j++) {
        if (covered_cases.find(j) != covered_cases.end() || i == j)
          continue;
        auto const& destination = nodes[j];

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
  }

  std::vector<Node> current_sol{};
  for (auto v : initial_sol) {
    current_sol.push_back(nodes[v]);
  }

  best_solution = current_sol;
}
