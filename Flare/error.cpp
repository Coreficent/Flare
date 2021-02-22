

#include <string>
#include <iostream>
#include <sdl/SDL.h>

using namespace std;

void fatalError(string errorString)
{
	cout << errorString << endl;
	int a;
	cin >> a;
	SDL_Quit();
}
