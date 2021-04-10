#include "Point.h"
#include "Sprite.h"

#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Flare
{
	Sprite::Sprite() noexcept {}

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

		const float half_width = this->width / 2.0f;
		const float half_height = this->height / 2.0f;

		vec3 top_left{ -half_width, -half_height, 1.0f };
		vec3 top_right{ half_width, -half_height, 1.0f };
		vec3 bottom_left{ -half_width, half_height, 1.0f };
		vec3 bottom_right{ half_width, half_height, 1.0f };

		const mat3 transform = calculate_matrix();

		top_left = transform * top_left;
		top_right = transform * top_right;
		bottom_left = transform * bottom_left;
		bottom_right = transform * bottom_right;


		result.push_back(Quad{ texture_id, Position{top_left.x, top_left.y}, Position{top_right.x, top_right.y}, Position{bottom_left.x, bottom_left.y}, Position{bottom_right.x, bottom_right.y}, get_uv() });

		for (auto& child : this->children)
		{
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

	mat3 Sprite::calculate_matrix()
	{
		return translate(mat3{}, vec2{ this->x, this->y });
	}

	vec4 Sprite::get_bound()
	{
		const mat3 translation = translate(mat3{}, vec2{ this->x - this->width / 2.0f, this->y - this->height / 2.0f });
		const vec3 top_left = translation * vec3{ 0.0f, 0.0f, 1.0f };
		const vec3 bottom_right = translation * vec3{ this->width , this->height, 1.0f };

		return vec4{ top_left.x, top_left.y, bottom_right.x , bottom_right.y };
	}

	vec4 Sprite::get_uv()
	{
		return vec4{ this->u_start,this->v_start,this->u_end,this->v_end };
	}
}
