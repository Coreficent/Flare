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
		this->glyphs_pointers.clear();
	}

	void QuadBatch::end()
	{
		this->glyphs_pointers.resize(this->glyphs.size());
		for (unsigned __int64 i{0}, l{(this->glyphs.size())}; i < l; ++i)
		{
			this->glyphs_pointers[i] = &this->glyphs[i];
		}
		this->sortGlyphs();
		this->createRenderBatches();
	}

	void QuadBatch::draw(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color)
	{
		this->glyphs.emplace_back(bound, uv, texture, depth, color);
	}

	void QuadBatch::render()
	{
		glBindVertexArray(this->vertexArrayID);
		for (auto& i : this->renderBatches)
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
			stable_sort(this->glyphs_pointers.begin(), this->glyphs_pointers.end(), this->compareFrontBack);
			break;
		case GlyphSortType::BACK_FRONT:

			stable_sort(this->glyphs_pointers.begin(), this->glyphs_pointers.end(), this->compareBackFront);
			break;
		case GlyphSortType::TEXTURE:

			stable_sort(this->glyphs_pointers.begin(), this->glyphs_pointers.end(), this->compareTexture);
			break;
		}
	}

	void QuadBatch::createRenderBatches()
	{
		if (this->glyphs_pointers.empty())
		{
			return;
		}
		vector<Vertex> vertices{};
		vertices.resize(this->glyphs_pointers.size() * 6);
		//TODO clean up


		/////////
		/*
		int vertex{ 0 };
		int offset{ 0 };
		this->renderBatches.emplace_back(offset, 6, this->glyphs_pointers[0]->texture);
		vertices[vertex++] = this->glyphs_pointers[0]->topLeft;
		vertices[vertex++] = this->glyphs_pointers[0]->bottomLeft;
		vertices[vertex++] = this->glyphs_pointers[0]->bottomRight;
		vertices[vertex++] = this->glyphs_pointers[0]->bottomRight;
		vertices[vertex++] = this->glyphs_pointers[0]->topRight;
		vertices[vertex++] = this->glyphs_pointers[0]->topLeft;
		offset += 6;

		for (auto glyph = 1; glyph < this->glyphs_pointers.size(); ++glyph)
		{
			if (this->glyphs_pointers[glyph]->texture != this->glyphs_pointers[glyph - 1]->texture)
			{
				this->renderBatches.emplace_back(offset, 6, this->glyphs_pointers[glyph]->texture);
			}
			else
			{
				this->renderBatches.back().vertexCount += 6;
			}
			vertices[vertex++] = this->glyphs_pointers[glyph]->topLeft;
			vertices[vertex++] = this->glyphs_pointers[glyph]->bottomLeft;
			vertices[vertex++] = this->glyphs_pointers[glyph]->bottomRight;
			vertices[vertex++] = this->glyphs_pointers[glyph]->bottomRight;
			vertices[vertex++] = this->glyphs_pointers[glyph]->topRight;
			vertices[vertex++] = this->glyphs_pointers[glyph]->topLeft;
			offset += 6;
		}
		*/
		///////
		// TODO int size?

		unsigned long long glyph{0}, length{this->glyphs_pointers.size()};
		auto offset{0}, vertex{0};
		GLuint previous_texture{0};
		do
		{
			if (this->glyphs_pointers[glyph]->texture != previous_texture)
			{
				this->renderBatches.emplace_back(offset, 6, this->glyphs_pointers[glyph]->texture);
			}
			else
			{
				this->renderBatches.back().vertexCount += 6;
			}
			vertices[vertex++] = this->glyphs_pointers[glyph]->topLeft;
			vertices[vertex++] = this->glyphs_pointers[glyph]->bottomLeft;
			vertices[vertex++] = this->glyphs_pointers[glyph]->bottomRight;
			vertices[vertex++] = this->glyphs_pointers[glyph]->bottomRight;
			vertices[vertex++] = this->glyphs_pointers[glyph]->topRight;
			vertices[vertex++] = this->glyphs_pointers[glyph]->topLeft;
			offset += 6;
			previous_texture = this->glyphs_pointers[glyph]->texture;
		}
		while (++glyph < length);


		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	bool QuadBatch::compareFrontBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}

	bool QuadBatch::compareBackFront(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}

	bool QuadBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return a->texture < b->texture;
	}
}
