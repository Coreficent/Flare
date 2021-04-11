#pragma once

#include "Matrix.h"
#include "Point.h"
#include "Quad.h"
#include "Vertex.h"
#include "Vial.h"

#include <gl/glew.h>
#include <memory>
#include <string>
#include <vector>

namespace Flare
{
	using namespace glm;
	using namespace std;

	class Sprite
	{

	public:
		Sprite() noexcept;
		Sprite(string texture_url);

		GLuint texture_id{ 0 };

		float x{ 0.0f };
		float y{ 0.0f };
		float width{ 0.0f };
		float height{ 0.0f };
		float rotation{ 0.0f };
		float scale_x{ 1.0f };
		float scale_y{ 1.0f };

		Sprite* parent{ nullptr };

		vector<shared_ptr<Sprite>> children{};

		void add_child(shared_ptr<Sprite> child) noexcept;
		void remove_child(shared_ptr<Sprite> child) noexcept;
		size_t child_count() noexcept;

		virtual void enter_frame() noexcept;
		virtual vector<Quad> graphics();

	protected:
		mat3 calculate_matrix();

	private:
		float u_start{ 0.0f };
		float u_end{ 1.0f };
		float v_start{ 0.0f };
		float v_end{ 1.0f };

		vec4 get_bound();
		vec4 get_uv();
	};
}
