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
			this->down_left.color = color;
			this->down_left.setPosition(bound.x, bound.y + bound.w);
			this->down_left.setUV(uv.x, uv.y + uv.w);

			this->top_left.color = color;
			this->top_left.setPosition(bound.x, bound.y);
			this->top_left.setUV(uv.x, uv.y);

			this->top_right.color = color;
			this->top_right.setPosition(bound.x + bound.z, bound.y);
			this->top_right.setUV(uv.x + uv.z, uv.y);

			this->down_right.color = color;
			this->down_right.setPosition(bound.x + bound.z, bound.y + bound.w);
			this->down_right.setUV(uv.x + uv.z, uv.y + uv.w);

			/////////////////////////////
			/*
			this->top_left.color = color;
			this->top_left.setPosition(bound.x, bound.y + bound.w);
			this->top_left.setUV(uv.x, uv.y + uv.w);

			this->top_right.color = color;
			this->top_right.setPosition(bound.x, bound.y);
			this->top_right.setUV(uv.x, uv.y);

			this->down_right.color = color;
			this->down_right.setPosition(bound.x + bound.z, bound.y);
			this->down_right.setUV(uv.x + uv.z, uv.y);

			this->down_left.color = color;
			this->down_left.setPosition(bound.x + bound.z, bound.y + bound.w);
			this->down_left.setUV(uv.x + uv.z, uv.y + uv.w);
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

			down_left.color = color;
			down_left.setPosition(destRect.x + tl.x, destRect.y + tl.y);
			down_left.setUV(uvRect.x, uvRect.y + uvRect.w);

			top_left.color = color;
			top_left.setPosition(destRect.x + bl.x, destRect.y + bl.y);
			top_left.setUV(uvRect.x, uvRect.y);

			top_right.color = color;
			top_right.setPosition(destRect.x + br.x, destRect.y + br.y);
			top_right.setUV(uvRect.x + uvRect.z, uvRect.y);

			down_right.color = color;
			down_right.setPosition(destRect.x + tr.x, destRect.y + tr.y);
			down_right.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
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

		Vertex down_left;
		Vertex top_left;
		Vertex top_right;
		Vertex down_right;
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
