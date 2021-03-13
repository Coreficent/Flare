#include "flare/FlareCore.h"
#include "gsl/gsl"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Hello World from Benchmark!\n";

	Flare::FlareCore core{ 500,1000 };
	core.run();

	return 0;
}
