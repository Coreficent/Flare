#pragma once

#include "Sprite.h"
#include <memory>

namespace Flare::Display
{
	class Container 
	{
	public:
		Container() noexcept;

		void add_child(std::shared_ptr<Flare::Display::Sprite> child);
		void remove_child (std::shared_ptr<Flare::Display::Sprite> child) noexcept;
		void render() const;

	private:
		std::vector<std::shared_ptr<Flare::Display::Sprite>> children;
	};
}
