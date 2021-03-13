#pragma once

#include "SpriteFont.h"
#include "Window.h"
#include "FrameManager.h"
#include "Audio.h"
#include "Renderer.h"
#include "Stage.h"
#include "Context.h"
#include "Key.h"
#include "Program.h"
#include "Game.h"

namespace Flare::Core
{
	using namespace std;

	class FlareCore
	{
	public:
		FlareCore(int windowWidth, int windowHeight);
		~FlareCore();

		void run();

		friend class Render;

		//friend class Display;

	private:
		// static FlareCore* core;

		Context context{};
		Window window{};
		Audio audio{};

		Key key{};
		Program program{};
		Game game{};

		Renderer renderer;

		FrameManager frame_manager{};
	};
}
