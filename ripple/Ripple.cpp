#include "flare/Flare_core.h"
#include "gsl/gsl"
#include <iostream>

int main(int argc, char** argv)
{
	using namespace Flare::Core;

	std::cout << "Hello World from Ripple!\n";

	Flare_core core{ 500,500 };
	core.run();

	return 0;
}
