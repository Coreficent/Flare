#include "flare/FlareCore.h"
#include "gsl/gsl"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Hello World from Ripple!\n";

	Flare::FlareCore core{ 500,500 };
	core.run();

	return 0;
}
