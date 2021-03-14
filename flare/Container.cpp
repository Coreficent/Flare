#include "Container.h"

namespace Flare::Display
{
	Container::Container() noexcept {}

	void Container::add_child(std::shared_ptr<Flare::Display::Sprite> child)
	{
		this->children.push_back(child);
	}

	void Container::remove_child(std::shared_ptr<Flare::Display::Sprite> child) noexcept
	{
		unsigned int i{ 0 };
		for (auto& c : this->children)
		{
			if (c == child)
			{
				break;
			}
			++i;
		}
		this->children.erase(this->children.begin() + i);
	}

	void Container::render() const
	{
		for (auto& c : this->children)
		{
			c->render();
		}
	}
}
