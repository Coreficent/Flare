#pragma once

#include "Audio.h"
#include "Key.h"
#include "Renderer.h"

namespace Flare
{
	class Program
	{
	public:
		void run(Flare::Renderer& renderer, Audio& audio);
	};
}
