#include "Container.h"

namespace Flare
{
	Container::Container()
		: Display{}
	{
	}


	Container::~Container()
	{
	}

	void Container::add_child(std::shared_ptr<Display> child)
	{
		this->children.push_back(child);
	}

	void Container::remove_child(std::shared_ptr<Display> child)
	{
		unsigned int i{0};
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
