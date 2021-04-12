#pragma once

#include "Camera.h"
#include "GLSL.h"
#include "Glyph.h"
#include "Sprite.h"

#include "Vertex.h"
#include "Vial.h"
#include <gl/glew.h>
#include <unordered_map>
#include <vector>

namespace Flare
{
	using namespace glm;
	using namespace std;
	using namespace Flare;

	class Render_batch
	{
	public:
		Render_batch(GLuint offset, GLuint vertex_count, GLuint texture) noexcept : offset{ offset }, vertex_count{ vertex_count }, texture{ texture } {};
		GLuint offset;
		GLuint vertex_count;
		GLuint texture;
	};

	class Renderer
	{
	public:
		Renderer(int width, int height);

		void initialize();
		void begin();
		void end();

		void draw(const vector<Quad>& quads);
		void draw(const Quad& quad);
		void draw(const Quad& quad, const vec4 uv, GLuint texture, float depth, const Color color);

		void finalize() noexcept;
		void render(Sprite& stage);

		Camera camera;
		int draw_call_count{0};

	private:
		void create_vertex_array() noexcept;
		void generate_batches();

		vector<Render_batch> render_batches{};
		Vial<Vertex> vertex_buffer{};
		Vial<Glyph> glyphs_vialxxx{};
		GLSL color_program{};
		GLuint vertex_buffer_id{};
		GLuint vertex_array_id{};
		GLuint previous_texture{};
	};
}
