#pragma once

#include "Camera.h"
#include "Container.h"
#include "GLSL.h"
#include "Glyph.h"
#include "SpriteFont.h"
#include "Vertex.h"
#include "Vial.h"
#include <gl/glew.h>
#include <unordered_map>
#include <vector>

namespace Flare::Render
{
	using namespace glm;
	using namespace Flare::Display;

	class RenderBatch
	{
	public:
		RenderBatch(GLuint offset, GLuint vertexCount, GLuint texture) noexcept : offset{ offset }, vertexCount{ vertexCount }, texture{ texture } {};

		GLuint offset;
		GLuint vertexCount;
		GLuint texture;
	};

	class Renderer
	{
	public:
		Renderer(int width, int height);

		void initialize();
		void begin();
		void end();
		void draw(const vec4 bound, const vec4 uv, GLuint texture, float depth, const Color color);
		void render();

		void renderNow();

		Camera camera;
		Container stage{};

		string text{};

	private:
		void createVertexArray();
		void createRenderBatches();

		std::vector<RenderBatch> renderBatches;

		Vial<Vertex> vertex_buffer{};

		Vial<Glyph> glyphs_vialxxx{};

		GLSL colorProgram;

		SpriteFont sprite_font{};

		GLuint vertex_buffer_id{};
		GLuint vertex_array_id{};
		GLuint previous_texture{};
	};
}
