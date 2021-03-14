#include "Benchmark_core.h"
#include <iostream>

int main(int argc, char** argv)
{
	using namespace std;
	using namespace Benchmark::Core;

	cout << "Hello from Benchmark!" << endl;

	Benchmark_core core{ 1000,500 };

	core.run();

	cout << "Bye World from Benchmark!" << endl;

	return 0;
}
