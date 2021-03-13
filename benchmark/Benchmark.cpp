#include "flare/Flare_core.h"
#include "gsl/gsl"
#include <iostream>

int main(int argc, char** argv)
{
	using namespace Flare::Core;

	std::cout << "Hello World from Benchmark!\n";

	Flare_core core{ 500,1000 };
	core.run();

	return 0;
}
