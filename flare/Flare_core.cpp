#include "Flare_core.h"
#include "debug.h"
#include "Sound.h"

#include <iostream>
#include <string>
#include <windows.h>

namespace Flare
{
	using namespace std;

	Flare_core::Flare_core(int window_width, int window_height) : window_width{ window_width }, window_height{ window_height }
	{
		dout << "Debug Mode" << endl;

#ifdef _DEBUG
		HWND windowHandle = GetConsoleWindow();
		ShowWindow(windowHandle, SW_SHOW);
#else
		HWND windowHandle = GetConsoleWindow();
		ShowWindow(windowHandle, SW_HIDE);
#endif

		/* audio */
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
		{
			printf("mixer initilization failed");
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024))
		{
			printf("audio failed to open");
		}
	}

	Flare_core::~Flare_core()
	{
		/* audio */
		Mix_CloseAudio();
		Mix_Quit();
	}

	void Flare_core::initialize() {}

	void Flare_core::run()
	{
		//Musice music = this->audio.load_music("music/x.ogg");
		//music.play(-1);

		//this->audio.initialize();
		this->renderer.initialize();
		this->initialize();

		while (!Key::is_down(SDLK_ESCAPE) && !Key::is_down(SDL_QUIT))
		{
			this->enter_frame();
			this->frame_manager.calculate_fps();
			Key::process();
			//this->program.run(this->renderer, this->audio);
			this->renderer.render(*this);
			this->window.update_window();
		}

		//music.stop();
	}
}
