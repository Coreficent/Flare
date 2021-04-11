#include "Point.h"
#include "Resource_manager.h"
#include "Sprite.h"

#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Flare
{
	Sprite::Sprite() noexcept
	{
	}

	Sprite::Sprite(string texture_url)
	{
		this->texture_id = Resource_manager::get_texture(texture_url).id;
	}

	void Sprite::add_child(shared_ptr<Sprite> child) noexcept
	{
		try
		{
			this->children.push_back(child);
			child->parent = this;
		}
		catch (...)
		{
			printf("failed to add child");
		}
	}

	void Sprite::remove_child(shared_ptr<Sprite> child) noexcept
	{
		try
		{
			auto it = find(this->children.begin(), this->children.end(), child);

			if (it != this->children.end())
			{
				const auto index = std::distance(this->children.begin(), it);
				this->children.erase(this->children.begin() + index);
				child->parent = nullptr;
			}
		}
		catch (...)
		{
			printf("failed to remove child");
		}
	}

	size_t Sprite::child_count() noexcept
	{
		return this->children.size();
	}

	float Sprite::global_x()
	{
		return this->global_position().x;
	}

	float Sprite::global_y()
	{
		return this->global_position().y;
	}

	vec3 Sprite::global_position()
	{
		return this->calculate_matrix() * vec3 { this->x, this->y, 1.0f };
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

		const mat3 transform = this->calculate_matrix();

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
		mat3 transform = scale(rotate(translate(mat3{}, vec2{ this->x, this->y }), radians(this->rotation)), vec2{ this->scale_x, this->scale_y });

		if (this->parent) {
			transform = this->parent->calculate_matrix() * transform;
		}

		return transform;
	}

	vec4 Sprite::get_uv()
	{
		return vec4{ this->u_start,this->v_start,this->u_end,this->v_end };
	}
}
