#include <string>
#include <iostream>
#include <sdl/SDL.h>
#include <cstdlib>

namespace Dove
{
	using namespace std;

	void fatalError(string errorString)
	{
		cout << errorString << endl;
		int a;
		cin >> a;
		SDL_Quit();
		exit(-1);
	}

	void debugPrint(string value)
	{
		cout << value;
	}
}
