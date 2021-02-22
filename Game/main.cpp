#include <iostream>

#include "flare/Core.h"
#include "gsl/gsl"

int main(int argc, char** argv)
{
	Flare::Core core{1600,900};
	core.run();

	return 0;
}
