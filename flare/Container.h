#pragma once

#include "Sprite.h"
#include <memory>

namespace Flare
{
	class Container : public Sprite
	{
	public:
		Container() noexcept;

		void add_child(std::shared_ptr<Sprite> child);
		void remove_child (std::shared_ptr<Sprite> child) noexcept;
		void render() const override;

	private:
		std::vector<std::shared_ptr<Sprite>> children;
	};
}
