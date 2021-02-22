#pragma once
#include <gl/glew.h>
#include "Vertex.h"
#include <vector>
#include <glm/detail/type_vec4.hpp>
#include "Glyph.h"

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

	class QuadBatch
	{
	public:
		QuadBatch();
		~QuadBatch();

		Glyph& next_glyph();

		void initialize();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end(); 
		void draw(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color);
		void render();



		//TODO temp public
		std::vector<Glyph> glyphs;

	private:


		void createVertexArray();
		void sortGlyphs();
		void createRenderBatches();

		static bool compareFrontBack(Glyph* a, Glyph* b);
		static bool compareBackFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		std::vector<Glyph*> glyphs_pointers;

		std::vector<RenderBatch> renderBatches;

		GlyphSortType sortType;

		GLuint vertexBufferID;
		GLuint vertexArrayID;

		unsigned int glyph_id{0};
	};
}
