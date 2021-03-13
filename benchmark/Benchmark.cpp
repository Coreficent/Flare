#include "flare/FlareCore.h"
#include "gsl/gsl"
#include <iostream>

int main(int argc, char** argv)
{
	using namespace Flare::Core;

	std::cout << "Hello World from Benchmark!\n";

	FlareCore core{ 500,1000 };
	core.run();

	return 0;
}
