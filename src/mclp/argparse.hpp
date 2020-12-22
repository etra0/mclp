#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef MCLP_MCLP_ARGPARSE_H_
#define MCLP_MCLP_ARGPARSE_H_

namespace mclp {

/*
 * arguments is in charge to do all the checkings about the arguments passed
 * when running the program. It'll contain all the parameters as well to pass
 * them to the respective classes & algorithms
 */
class arguments {
public:
  std::string nodes;
  std::string demand;

  // number of available servers
  uint32_t p;

  // maximum radius
  uint32_t S;

  // Number of iterations to do while doing the Tabu Search
  uint32_t it;

  arguments() : nodes(), demand(), p(0), S(0), it(0){};

  int parse(const int argc, const char *argv[]);

  // Print the `how to use` message. This function gets triggered when you
  // input incorrect parameters on when you do `--help`
  static void usage();

  // Run the program with **arbitrary** default arguments (mainly used for
  // testing), those are:
  //
  // nodes = "./instances/SJC324.txt"
  // demand = "./instances/demand-SJC324.dat"
  // p = 5
  // S = 1200
  void default_arguments();
};

} // namespace mclp
#endif // MCLP_MCLP_ARGPARSE_H_
