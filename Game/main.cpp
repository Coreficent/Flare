#include <iostream>
#include <dove/Core.h>

int main(int argc, char** argv)
{
	Dove::Core dove{1600,900};
	dove.run();
	
	return 0;
}
