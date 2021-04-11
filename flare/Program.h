#pragma once
#include "Key.h"
#include "Audio.h"
#include "Renderer.h"

namespace Flare
{
	class Program
	{
	public:
		void run(Flare::Renderer& renderer, Audio& audio);
	};
}
