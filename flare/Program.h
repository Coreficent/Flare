#pragma once

#include "Audio.h"
#include "Key.h"
#include "Renderer.h"

namespace Flare
{
	class Program
	{
	public:
		void running(Flare::Renderer& renderer, Audio& audio);
	};
}
