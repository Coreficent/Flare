#pragma once
#include "Key.h"
#include "Audio.h"
#include "Renderer.h"

namespace Flare
{
	class Program
	{
	public:
		void run(Key& key, Flare::Render::Renderer& renderer, Audio& audio);
	};
}
