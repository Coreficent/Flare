#pragma once

#include "Camera.h"
#include "GLSL.h"
#include "Glyph.h"
#include "SpriteFont.h"
#include "Vertex.h"
#include "Vial.h"

#include <gl/glew.h>
#include <unordered_map>
#include <vector>

namespace Flare
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_BACK,
		BACK_FRONT,
		TEXTURE
	};

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

		Glyph& next_glyph();

		void initialize();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4 bound, const glm::vec4 uv, GLuint texture, float depth, const Color color);
		void render();

		void renderNow();

		Camera camera;
		GLuint t_id{ 0 };
		GLuint a_id{ 0 };

		std::unordered_map<GLuint, Vial<Vertex>> hash{};

	private:
		void createVertexArray();
		void sortGlyphs();
		void createRenderBatches();

		void _____renderCake();

		static bool compareFrontBack(Glyph* a, Glyph* b);
		static bool compareBackFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		std::vector<Glyph*> glyphs_pointers;

		std::vector<RenderBatch> renderBatches;

		Vial<Glyph> glyphs_vial{};

		GLSL colorProgram;

		SpriteFont sprite_font{};

		GlyphSortType sortType;

		GLuint vertexBufferID;
		GLuint vertexArrayID;
	};
}
