#pragma once

#include "Audio.h"
#include "Context.h"
#include "Frame_manager.h"
#include "Key.h"
#include "Program.h"
#include "Renderer.h"
#include "Text_field.h"
#include "Window.h"

namespace Flare
{
	using namespace std;
	using namespace Flare;
	using namespace Flare;

	class Flare_core : public Sprite
	{

	public:
		Flare_core(int window_width, int window_height);
		Flare_core(const Flare_core& value) = default;
		Flare_core(Flare_core&& value) = default;
		Flare_core& operator=(const Flare_core& value) = default;
		Flare_core& operator=(Flare_core&& value) = default;
		virtual ~Flare_core() = default;

		virtual void initialize() noexcept;

		void running();

		int window_width;
		int window_height;

	protected:
		Audio audio{};
		Context context{};
		Frame_manager frame_manager{};
		Program program{};
		Renderer renderer{ window_width, window_height };
		Window window{ "Flare", window_width, window_height };
	};
}
