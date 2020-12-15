#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

class Arguments {
	public:
	std::string nodes;
	std::string demand;

	// number of available servers
	int p;

	// maximum radius
	int S;

	// Number of iterations
	int it;

	Arguments(const int argc, const char *argv[]);
	static void usage();
	void default_arguments();
};
