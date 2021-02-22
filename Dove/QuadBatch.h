#pragma once
#include <gl/glew.h>
#include "Vertex.h"
#include <glm/detail/type_vec3.hpp>
#include <vector>
#include <memory>
#include <glm/detail/type_vec4.hpp>
#include <glm/detail/type_vec2.hpp>

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

		Glyph()
			:texture{0},depth{0.0f}
		{
			
		}

		Glyph(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color)
			: texture{texture}, depth{depth}
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

			/////////////////////////////
			/*
			this->bottomLeft.color = color;
			this->bottomLeft.setPosition(bound.x, bound.y + bound.w);
			this->bottomLeft.setUV(uv.x, uv.y + uv.w);

			this->bottomRight.color = color;
			this->bottomRight.setPosition(bound.x, bound.y);
			this->bottomRight.setUV(uv.x, uv.y);

			this->topRight.color = color;
			this->topRight.setPosition(bound.x + bound.z, bound.y);
			this->topRight.setUV(uv.x + uv.z, uv.y);

			this->topLeft.color = color;
			this->topLeft.setPosition(bound.x + bound.z, bound.y + bound.w);
			this->topLeft.setUV(uv.x + uv.z, uv.y + uv.w);
			*/
		}

		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle)
			: texture(Texture), depth(Depth)
		{
			glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

			// Get points centered at origin
			glm::vec2 tl(-halfDims.x, halfDims.y);
			glm::vec2 bl(-halfDims.x, -halfDims.y);
			glm::vec2 br(halfDims.x, -halfDims.y);
			glm::vec2 tr(halfDims.x, halfDims.y);

			// Rotate the points
			tl = rotatePoint(tl, angle) + halfDims;
			bl = rotatePoint(bl, angle) + halfDims;
			br = rotatePoint(br, angle) + halfDims;
			tr = rotatePoint(tr, angle) + halfDims;

			topLeft.color = color;
			topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
			topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			bottomLeft.color = color;
			bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
			bottomLeft.setUV(uvRect.x, uvRect.y);

			bottomRight.color = color;
			bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
			bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

			topRight.color = color;
			topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
			topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}

		glm::vec2 rotatePoint(const glm::vec2& pos, float angle)
		{
			glm::vec2 newv;
			newv.x = pos.x * cos(angle) - pos.y * sin(angle);
			newv.y = pos.x * sin(angle) + pos.y * cos(angle);
			return newv;
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

		//TODO temp public
		std::vector<Glyph> glyphs;

	private:
		std::vector<Glyph*> glyphs_pointers;
		
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
