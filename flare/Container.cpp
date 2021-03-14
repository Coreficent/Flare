#include "Container.h"

namespace Flare::Display
{
	Container::Container() noexcept {}

	void Container::add_child(Sprite child)
	{
		this->children.push_back(child);
	}

	void Container::render() const
	{
		
	}
}
