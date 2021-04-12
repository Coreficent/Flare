#pragma once

#include "Frame_manager.h"
#include "Key.h"
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
		virtual ~Flare_core();

		virtual void initialize();

		void run();

		int window_width;
		int window_height;

	protected:
		Frame_manager frame_manager{};
		Renderer renderer{ window_width, window_height };
		Window window{ "", window_width, window_height };
	};
}
