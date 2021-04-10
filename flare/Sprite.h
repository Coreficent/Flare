#pragma once

#include "Matrix.h"
#include "Point.h"

#include "Quad.h"
#include "Vertex.h"
#include "Vial.h"
#include <gl/glew.h>
#include <memory>
#include <vector>

namespace Flare
{
	using namespace glm;
	using namespace std;

	class Sprite
	{

	public:
		Sprite() noexcept;
		Sprite(const Sprite& value) = default;
		Sprite(Sprite&& value) = default;
		Sprite& operator=(const Sprite& value) = default;
		Sprite& operator=(Sprite&& value) = default;
		virtual ~Sprite() = default;

		GLuint texture_id{ 0 };
		float x{ 0.0f };
		float y{ 0.0f };
		float width{ 0.0f };
		float height{ 0.0f };

		vec4 get_bound();
		vec4 get_uv();
		vector<Quad> graphics();
		vector<shared_ptr<Sprite>> children{};

		void add_child(shared_ptr<Sprite> child);
		void remove_child(shared_ptr<Sprite> child);
		int child_count() noexcept;

		virtual void enter_frame() noexcept;

	private:
		Matrix matrix{};

		Color color{ 255,255,255 ,255 };

		float u_start{ 0.0f };
		float u_end{ 1.0f };
		float v_start{ 0.0f };
		float v_end{ 1.0f };

		Point locate_vertex(float x, float y) const;
	};
}
