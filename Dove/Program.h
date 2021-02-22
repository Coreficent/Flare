#pragma once
#include "Key.h"
#include "Audio.h"
#include "Renderer.h"

namespace Flare
{
	class Program
	{
	public:
		Program();
		~Program();

		void run(Key& key, Renderer& renderer, Audio& audio);
	};
}
