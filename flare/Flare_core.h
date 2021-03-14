#pragma once

#include "Audio.h"
#include "Context.h"
#include "FrameManager.h"
#include "Game.h"
#include "Key.h"
#include "Program.h"
#include "Renderer.h"
#include "SpriteFont.h"
#include "Window.h"

namespace Flare::Core
{
	using namespace std;

	class Flare_core
	{
	public:
		Flare_core(int windowWidth, int windowHeight);
		void run();

	private:
		Context context{};
		Window window{};
		Audio audio{};

		Key key{};
		Program program{};
		Game game{};

		Flare::Render::Renderer renderer;

		FrameManager frame_manager{};
	};
}
