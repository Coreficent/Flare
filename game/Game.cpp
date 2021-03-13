#include "flare/FlareCore.h"
#include "gsl/gsl"
#include <iostream>

int main(int argc, char** argv)
{
	using namespace Flare::Core;

	FlareCore core{1600,900};
	core.run();

	return 0;
}
