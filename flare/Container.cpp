#include "Container.h"

namespace Flare::Display
{
	Container::Container() noexcept {}

	void Container::add_child(Sprite child)
	{
		this->children.push_back(child);
	}

	vector<Quad> Container::get_quads()
	{
		vector<Quad> result{};

		for (auto& child : this->children) {
			result.push_back(child.get_quad());
		}

		return result;
	}
}
