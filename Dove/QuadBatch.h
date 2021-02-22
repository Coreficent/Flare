#pragma once
#include <gl/glew.h>
#include "Vertex.h"
#include <glm/detail/type_vec3.hpp>
#include <vector>
#include <memory>
#include <glm/detail/type_vec4.hpp>

namespace Dove
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_BACK,
		BACK_FRONT,
		TEXTURE
	};

	class Glyph
	{
	public:
		Glyph(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color) : texture{texture}, depth{depth}
		{
			this->topLeft.color = color;
			this->topLeft.setPosition(bound.x, bound.y + bound.w);
			this->topLeft.setUV(uv.x, uv.y + uv.w);

			this->bottomLeft.color = color;
			this->bottomLeft.setPosition(bound.x, bound.y);
			this->bottomLeft.setUV(uv.x, uv.y);

			this->bottomRight.color = color;
			this->bottomRight.setPosition(bound.x + bound.z, bound.y);
			this->bottomRight.setUV(uv.x + uv.z, uv.y);

			this->topRight.color = color;
			this->topRight.setPosition(bound.x + bound.z, bound.y + bound.w);
			this->topRight.setUV(uv.x + uv.z, uv.y + uv.w);
		}

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex bottomRight;
		Vertex topRight;
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

		void initialize();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color);
		void render();

	private:
		std::vector<Glyph*> glyphs_pointers;
		std::vector<Glyph> glyphs;
		std::vector<RenderBatch> renderBatches;

		GlyphSortType sortType;

		GLuint vertexBufferID;
		GLuint vertexArrayID;


		void createVertexArray();
		void sortGlyphs();
		void createRenderBatches();


		static bool compareFrontBack(Glyph* a, Glyph* b);
		static bool compareBackFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
	};
}
