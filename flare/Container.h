#pragma once

#include "Display.h"
#include <memory>

namespace Flare
{
	class Container : public Display
	{
	public:
		Container() noexcept;

		void add_child(std::shared_ptr<Display> child);
		void remove_child (std::shared_ptr<Display> child) noexcept;
		void render() const override;

	private:
		std::vector<std::shared_ptr<Display>> children;
	};
}
