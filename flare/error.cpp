#include <string>
#include <iostream>
#include <sdl/SDL.h>
#include <cstdlib>
#include <fstream>


namespace Flare
{
	using namespace std;

	void output_error(string errorString)
	{
		ofstream error_log;
		error_log.open("errorlog.txt");
		error_log << errorString << endl;
		error_log.close();

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "See Error Log.", nullptr);
		SDL_Quit();
		exit(-1);
	}

	void debug_print(string value)
	{
		cout << value;
	}
}
