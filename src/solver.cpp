#include <mclp/solver.hpp>
#include <mclp/utils.hpp>

void Solver::print() { this->domain.print(); }

void Solver::find_initial_solution() {
    // Do a deep copy to avoid some UB.
    auto nodes = std::vector(this->domain.nodes);
    auto loop_counter = this->p;
    std::set<uint32_t> initial_sol {};

    while (loop_counter--) {
        uint32_t best_case_p = 0;
        uint32_t best_case_counter = 0;

        for (size_t i = 0; i < nodes.size(); i++) {
            const auto& point = nodes[i];
            uint32_t counter = 0;

            // Check the count of nodes that are in the specified radius
            for (auto point2 : nodes) {
                auto distance = utils::eucl_distance(point, point2);
                if (distance <= S) {
                    counter++;
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
}
