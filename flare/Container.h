#pragma once

#include "Quad.h"
#include "Sprite.h"

#include <vector>

namespace Flare::Display
{
	using namespace std;
	using namespace Flare::Display;

	class Container
	{
	public:
		Container() noexcept;

		void add_child(Sprite child);
		
		vector<Quad> get_quads();

	private:
		vector<Sprite> children;
	};
}
