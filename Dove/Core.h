#pragma once

#include "SpriteFont.h"
#include "Window.h"
#include "FrameManager.h"
#include "Audio.h"
#include "Renderer.h"
#include "Stage.h"
#include "Media.h"
#include "Key.h"
#include "Program.h"
#include "Game.h"


namespace Dove
{
	using namespace std;

	class Core
	{
	public:
		Core(int windowWidth, int windowHeight);
		~Core();

		void run();

		friend class Render;

		friend class Display;

	private:
		static Core* core;

		Media media{};
		Window window{};
		Audio audio{};

		Key key{};
		Program program{};
		Game game{};

		Renderer renderer;

		FrameManager frame_manager{};

	};
}
