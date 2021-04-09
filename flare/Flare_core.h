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

namespace Flare
{
	using namespace std;
	using namespace Flare;
	using namespace Flare;

	class Flare_core
	{

	public:
		Flare_core(int window_width, int window_height);
		Flare_core(const Flare_core& value) = default;
		Flare_core(Flare_core && value) = default;
		Flare_core& operator=(const Flare_core & value) = default;
		Flare_core& operator=(Flare_core && value) = default;
		virtual ~Flare_core() = default;

		Container& get_stage() noexcept;

		void run();

		virtual void initialize() noexcept;
		virtual void enter_frame() noexcept;

		int window_width;
		int window_height;

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
