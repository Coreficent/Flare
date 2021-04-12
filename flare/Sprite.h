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
		Sprite(const Sprite& sprite) = delete;
		Sprite(Sprite&& sprite) = delete;
		Sprite& operator=(const Sprite& sprite) = delete;
		Sprite& operator=(Sprite&& ssprite) = delete;
		virtual ~Sprite() = default;

		size_t child_count() noexcept;
		size_t total_child_count() noexcept;
		virtual bool hit_test_object(Sprite& sprite);
		virtual vector<Quad> graphics();
		virtual void enter_frame();
		void add_child(shared_ptr<Sprite> child);
		void remove_child(shared_ptr<Sprite> child);

		GLuint texture_id{ 0 };
		Sprite* parent{ nullptr };
		float global_x();
		float global_y();
		float height{ 0.0f };
		float rotation{ 0.0f };
		float scale_x{ 1.0f };
		float scale_y{ 1.0f };
		float width{ 0.0f };
		float x{ 0.0f };
		float y{ 0.0f };
		vector<shared_ptr<Sprite>> children{};

	protected:
		mat3 calculate_matrix();

	private:
		vec3 global_position();
		vec4 get_uv();

		float u_end{ 1.0f };
		float u_start{ 0.0f };
		float v_end{ 1.0f };
		float v_start{ 0.0f };
	};
}
