#include "Container.h"

namespace Flare::Display
{
	using namespace std;

	Container::Container() noexcept {}

	Container::~Container()
	{
	}

	void Container::add_child(shared_ptr<Sprite> child)
	{
		this->children.push_back(child);
	}

	void Container::reomve_last_child() noexcept
	{
		if (!this->children.empty()) {
			this->children.pop_back();
		}
	}

	vector<Quad> Container::get_quads()
	{
		vector<Quad> result{};

		for (auto& child : this->children) {
			result.push_back(child->get_quad());
		}

		return result;
	}

	void Container::enter_frame() noexcept
	{
		for (auto& child : this->children) {
			child->enter_frame();
		}
	}

	int Container::get_size() noexcept
	{
		return this->children.size();
	}
}
