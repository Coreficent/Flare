#include "flare/Flare_core.h"
#include "gsl/gsl"
#include <iostream>

int main(int argc, char** argv)
{
	using namespace Flare::Core;

	Flare_core core{1600,900};
	core.run();

	return 0;
}
