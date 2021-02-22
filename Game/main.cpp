#include <iostream>

#include "dove/Core.h"
#include "gsl/gsl"

int main(int argc, char** argv)
{
	Dove::Core core{1600,900};
	core.run();

	return 0;
}
