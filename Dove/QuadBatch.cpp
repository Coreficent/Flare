#include "QuadBatch.h"
#include <glm/detail/type_vec4.hpp>
#include <algorithm>

using namespace std;

namespace Dove
{
	QuadBatch::QuadBatch(): glyphs{}, sortType{GlyphSortType::NONE}, vertexBufferID{0}, vertexArrayID{0}
	{
	}


	QuadBatch::~QuadBatch()
	{
	}

	void QuadBatch::initialize()
	{
		this->createVertexArray();
	}

	void QuadBatch::begin(GlyphSortType sortType)
	{
		this->sortType = sortType;
		this->renderBatches.clear();
		this->glyphs.clear();
	}

	void QuadBatch::end()
	{
		this->sortGlyphs();
		this->createRenderBatches();
	}

	void QuadBatch::draw(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color)
	{
		this->glyphs.push_back(make_shared<Glyph>(Glyph{texture,depth,{bound.x,bound.y + bound.w,color,uv.x,uv.y + uv.w},{bound.x,bound.y,color,uv.x,uv.y},{bound.x + bound.z,bound.y,color,uv.x + uv.z,uv.y},{bound.x + bound.z,bound.y + bound.w,color,uv.x + uv.z,uv.y + uv.w}}));
	}

	void QuadBatch::render()
	{
		glBindVertexArray(this->vertexArrayID);
		for(auto& i : this->renderBatches)
		{
			glBindTexture(GL_TEXTURE_2D, i.texture);
			glDrawArrays(GL_TRIANGLES, i.offset, i.vertexCount);
		}

		glBindVertexArray(0);
	}

	void QuadBatch::createVertexArray()
	{
		if (!this->vertexArrayID)
		{
			glGenVertexArrays(1, &this->vertexArrayID);
		}
		glBindVertexArray(this->vertexArrayID);
		if (!this->vertexBufferID)
		{
			glGenBuffers(1, &this->vertexBufferID);
		}
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//for position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
		//for color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
		//for texture
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));

		glBindVertexArray(0);
		// TODO where is unbind for verex buffer
	}

	void QuadBatch::sortGlyphs()
	{
		//TODO use sort?
		switch (this->sortType)
		{
		case GlyphSortType::NONE:

			break;
		case GlyphSortType::FRONT_BACK:
			stable_sort(this->glyphs.begin(), this->glyphs.end(), this->compareFrontBack);
			break;
		case GlyphSortType::BACK_FRONT:

			stable_sort(this->glyphs.begin(), this->glyphs.end(), this->compareBackFront);
			break;
		case GlyphSortType::TEXTURE:

			stable_sort(this->glyphs.begin(), this->glyphs.end(), this->compareTexture);
			break;
		}
	}

	void QuadBatch::createRenderBatches()
	{
		vector <Vertex> vertices;
		vertices.resize(this->glyphs.size()*6);
		//TODO clean up
		if(this->glyphs.empty())
		{
			return;
		}
		int vertex{0};
		int offset{ 0 };
		this->renderBatches.emplace_back(offset, 6, this->glyphs[0]->texture);
		vertices[vertex++] = this->glyphs[0]->topLeft;
		vertices[vertex++] = this->glyphs[0]->bottomLeft;
		vertices[vertex++] = this->glyphs[0]->bottomRight;
		vertices[vertex++] = this->glyphs[0]->bottomRight;
		vertices[vertex++] = this->glyphs[0]->topRight;
		vertices[vertex++] = this->glyphs[0]->topLeft;
		offset += 6;

		for(int glyph = 1; glyph<this->glyphs.size();++glyph)
		{
			if(this->glyphs[glyph]->texture!=this->glyphs[glyph-1]->texture){
				this->renderBatches.emplace_back(offset, 6, this->glyphs[0]->texture);
			}
			else
			{
				this->renderBatches.back().vertexCount += 6;
			}
			vertices[vertex++] = this->glyphs[glyph]->topLeft;
			vertices[vertex++] = this->glyphs[glyph]->bottomLeft;
			vertices[vertex++] = this->glyphs[glyph]->bottomRight;
			vertices[vertex++] = this->glyphs[glyph]->bottomRight;
			vertices[vertex++] = this->glyphs[glyph]->topRight;
			vertices[vertex++] = this->glyphs[glyph]->topLeft;
			offset += 6;

		}

		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}


	bool QuadBatch::compareFrontBack(shared_ptr<Glyph> a, shared_ptr<Glyph> b)
	{
		return a->depth < b->depth;
	}

	bool QuadBatch::compareBackFront(shared_ptr<Glyph> a, shared_ptr<Glyph> b)
	{
		return a->depth > b->depth;
	}

	bool QuadBatch::compareTexture(shared_ptr<Glyph> a, shared_ptr<Glyph> b)
	{
		return a->texture < b->texture;
	}
}
