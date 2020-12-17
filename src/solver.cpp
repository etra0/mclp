#include <mclp/solver.hpp>

void Solver::print() {
  for (auto n : best_solution) {
    n.print();
  }
}

void Solver::find_initial_solution() {
  // Do a deep copy to avoid some UB.
  auto nodes = std::vector<Node>(this->domain.nodes);
  auto loop_counter = this->p;
  std::set<uint32_t> initial_sol{};

  while (loop_counter--) {
    uint32_t best_case_p = 0;
    uint32_t best_case_counter = 0;

    for (size_t i = 0; i < nodes.size(); i++) {
      const auto &origin = nodes[i];
      uint32_t counter = 0;

      // Check the count of nodes that are in the specified radius
      for (auto destination : nodes) {
        auto distance = utils::eucl_distance(origin, destination);
        if (distance <= S) {
          counter += destination.demand;
        }
      }

      if (counter > best_case_counter &&
          initial_sol.find(static_cast<uint32_t>(i)) == initial_sol.end()) {
        best_case_counter = counter;
        best_case_p = static_cast<uint32_t>(i);
      }
    }

    initial_sol.insert(best_case_p);
  }

  for (auto v : initial_sol) {
    best_solution.push_back(nodes[v]);
  }
}
