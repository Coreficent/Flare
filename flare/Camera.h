#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace Flare
{
	using namespace glm;

	class Camera
	{
	public:
		Camera(int window_width, int window_height);

		float get_scale() const noexcept;
		void set_position(const vec2& position) noexcept;
		void set_scale(float scale) noexcept;
		void update();

		mat4 get_camera_matrix() const noexcept;
		vec2 get_position() const noexcept;
		vec2 global_to_local(vec2 global_position) const;

	private:
		bool update_required;
		float scale;
		int window_height;
		int window_width;
		mat4 camera_matrix;
		mat4 identity_matrix;
		mat4 orthogonal_matrix;
		vec2 position;
	};
}
