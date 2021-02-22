#pragma once
#include "Key.h"
#include "Audio.h"
#include "Renderer.h"

namespace Dove
{
	class Program
	{
	public:
		Program();
		~Program();

		void run(Key& key, Renderer& renderer, Audio& audio);
	};
}
