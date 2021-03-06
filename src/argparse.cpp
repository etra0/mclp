#include <mclp/argparse.hpp>

namespace mclp {

int arguments::parse(const int argc, const char *argv[]) {
  if (argc >= 2 && argc < 6) {
    std::string arg = argv[1];
    if (arg == "--default") {
      std::cout << "Using default arguments" << std::endl;
      this->default_arguments();
      return 1;
    } else if (arg == "--help") {
      arguments::usage();
      return 0;
    } else {
      arguments::usage();
      throw std::invalid_argument("Some arguments are missing");
    }
  } else if (argc > 6 || argc == 1) {
    arguments::usage();
    throw std::invalid_argument("Incorrect arguments");
  }

  nodes = argv[1];
  demand = argv[2];

  std::string p_ = argv[3];
  std::string S_ = argv[4];
  std::string it_ = argv[5];

  try {
    p = static_cast<uint32_t>(std::stoul(p_));
    S = static_cast<uint32_t>(std::stoul(S_));
    it = static_cast<uint32_t>(std::stoul(it_));
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument("Can't parse one of the arguments");
  }

  return 1;
}

void arguments::default_arguments() {
  nodes = "./instances/SJC324.txt";
  demand = "./instances/demand-SJC324.dat";
  p = 5;
  S = 1200;
  it = 10;
}

void arguments::usage() {
  std::cout << u8"MCLP Solver by Sebastián Aedo\n" << std::endl;
  std::cout << "USAGE: \n"
               "\t./bin/mclp <nodes_file> <demand_file> <p> <S> <it>\n"
               "\nwhere:\n"
               "\t* p: Number of servers\n"
               "\t* S: Maximum radius\n"
               "\t* it: Number of iterations\n";
}

} // namespace mclp
