#pragma once
#include <gl/glew.h>
#include "Vertex.h"
#include <vector>
#include "Glyph.h"
#include "GLSL.h"
#include "Camera.h"
#include "SpriteFont.h"
#include "Vial.h"
#include "Batch.h"
#include <memory>

namespace Dove
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
		RenderBatch(GLuint offset, GLuint vertexCount, GLuint texture) : offset{offset}, vertexCount{vertexCount}, texture{texture}
		{
		}

		GLuint offset;
		GLuint vertexCount;
		GLuint texture;
	};

	class Renderer
	{
	public:
		Renderer(int width, int height);
		~Renderer();

		Glyph& next_glyph();

		void initialize();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void draw(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color);
		void render();
		void end();
		void renderNow();

		//TODO temp public //
		Camera camera;

	private:


		void createVertexArray();
		void sortGlyphs();
		void createRenderBatches();

		static bool compareFrontBack(Glyph* a, Glyph* b);
		static bool compareBackFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		std::vector<Glyph*> glyphs_pointers;

		std::vector<RenderBatch> renderBatches;

		Vial<Glyph> glyphs_vial{};

		//std::vector<Glyph> glyphs;

		Batch* batch{};
		GLSL colorProgram;


		SpriteFont sprite_font{};

		GlyphSortType sortType;

		GLuint vertexBufferID;
		GLuint vertexArrayID;

		//unsigned int glyph_id{0};
	};
}
