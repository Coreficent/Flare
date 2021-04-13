#include "Camera.h"

namespace Flare
{
	using namespace glm;

	Camera::Camera(int window_width, int window_height)
		: position{0.0f,0.0f}, camera_matrix(1.0f), orthogonal_matrix{ortho(0.0f, static_cast<float>(window_width), static_cast<float>(window_height), 0.0f)}, identity_matrix{1.0f}, scale{1.0f}, window_width{window_width}, window_height{window_height}, update_required{true}
	{
	}

	void Camera::set_position(const vec2& position) noexcept
	{
		this->position = position;
		this->update_required = true;
	}

	vec2 Camera::get_position() const noexcept
	{
		return this->position;
	}

	void Camera::set_scale(float scale) noexcept
	{
		this->scale = scale;
		this->update_required = true;
	}

	float Camera::get_scale() const noexcept
	{
		return this->scale;
	}

	mat4 Camera::get_camera_matrix() const noexcept
	{
		return this->camera_matrix;
	}

	void Camera::update()
	{
		if (this->update_required)
		{
			const vec3 translate{this->position.x + this->window_width / 2, this->position.y + this->window_height / 2, 0.0f};
			this->camera_matrix = glm::translate(this->orthogonal_matrix, translate);
			const vec3 scale{this->scale,this->scale,0.0f};
			this->camera_matrix = glm::scale(this->identity_matrix, scale) * this->camera_matrix;
			this->update_required = false;
		}
	}

	vec2 Camera::global_to_local(vec2 global_position) const
	{
		global_position -= vec2(this->window_width / 2, this->window_height / 2);
		global_position /= this->scale;
		global_position += this->position;

		return global_position;
	}
}
