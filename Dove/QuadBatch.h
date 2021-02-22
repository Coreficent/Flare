#pragma once
#include <gl/glew.h>
#include "Vertex.h"
#include <glm/detail/type_vec3.hpp>
#include <vector>
#include <memory>

namespace Dove
{
	enum class GlyphSortType
	{
		NONE, FRONT_BACK,BACK_FRONT,TEXTURE
	};
	struct Glyph
	{
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
		RenderBatch(GLuint offset, GLuint vertexCount, GLuint texture) : offset{ offset }, vertexCount{ vertexCount }, texture{ texture } {

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
		std::vector<std::shared_ptr<Glyph>> glyphs;
		std::vector<RenderBatch> renderBatches;

		GlyphSortType sortType;

		GLuint vertexBufferID;
		GLuint vertexArrayID;
		

		void createVertexArray();
		void sortGlyphs();
		void createRenderBatches();


		static bool compareFrontBack(std::shared_ptr<Glyph> a, std::shared_ptr<Glyph> b);
		static bool compareBackFront(std::shared_ptr<Glyph> a, std::shared_ptr<Glyph> b);
		static bool compareTexture(std::shared_ptr<Glyph> a, std::shared_ptr<Glyph> b);
	};
}
