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

		void run();

		friend class Render;
	private:
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
