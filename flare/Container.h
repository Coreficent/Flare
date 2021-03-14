#pragma once

#include "Sprite.h"
#include <memory>
#include <vector>

namespace Flare::Display
{
	using namespace Flare::Display;

	class Container
	{
	public:
		Container() noexcept;

		void add_child(Sprite child);
		
		void render() const;

	private:
		std::vector<Sprite> children;
	};
}
