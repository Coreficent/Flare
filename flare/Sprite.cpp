#include "Point.h"
#include "Sprite.h"

#include <algorithm>
#include <iostream>

namespace Flare
{
	Sprite::Sprite() noexcept {}

	vec4 Sprite::get_bound()
	{
		return vec4{ this->x, this->y, this->width , this->height };
	}

	vec4 Sprite::get_uv()
	{
		return vec4{ this->u_start,this->v_start,this->u_end,this->v_end };
	}

	void Sprite::add_child(shared_ptr<Sprite> child)
	{
		this->children.push_back(child);
	}

	void Sprite::remove_child(shared_ptr<Sprite> child)
	{
		auto it = find(this->children.begin(), this->children.end(), child);

		int index{ -1 };
		if (it != this->children.end())
		{
			index = std::distance(this->children.begin(), it);
			this->children.erase(this->children.begin() + index);
		}
	}

	int Sprite::child_count() noexcept
	{
		return this->children.size();
	}

	vector<Quad> Sprite::graphics()
	{
		vector<Quad> result{};

		result.push_back(Quad{ texture_id, get_bound(), get_uv() });

		for (auto& child : this->children) {
			auto& graphics = child->graphics();
			result.insert(result.end(), graphics.begin(), graphics.end());
		}

		return result;
	}

	void Sprite::enter_frame() noexcept
	{
		for (auto& child : this->children)
		{
			child->enter_frame();
		}
	}
}
