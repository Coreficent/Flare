#pragma once

#include "Audio.h"
#include "Context.h"
#include "Frame_manager.h"
#include "Game.h"
#include "Key.h"
#include "Program.h"
#include "Renderer.h"
#include "SpriteFont.h"
#include "Window.h"

namespace Flare::Core
{
	using namespace std;
	using namespace Flare::Display;
	using namespace Flare::Frame;
	using namespace Flare::Render;

	class Flare_core
	{

	public:
		Flare_core(int windowWidth, int windowHeight);

		Container& get_stage() noexcept;

		void run();
		virtual void enter_frame() noexcept;

	protected:
		Context context{};
		Window window{};
		Audio audio{};

		Key key{};
		Program program{};
		Game game{};

		Renderer renderer;

		Frame_manager frame_manager{};
	};
}
