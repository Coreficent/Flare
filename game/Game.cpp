#include "Game_core.h"

#include <flare/Flare_core.h>
#include <gsl/gsl>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace Game;

	Game_core core{ 1'600, 1'000 };
	core.running();

	return 0;
}
