#include <iostream>
#include <dove/Core.h>
#include <gsl/gsl>


int main(int argc, char** argv)
{
	Dove::Core core{1600,900};
	core.run();
	int arr[10];           // BAD, warning 26494 will be fired
	int* p = arr;  // BAD, warning 26485 will be fired
	return 0;
}
