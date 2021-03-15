#include "Quad.h"
#include "Renderer.h"
#include "Resource_manager.h"
#include "Sprite.h"
#include "debug.h"
#include "mathematics.h"
#include <algorithm>
#include <glm/detail/type_vec4.hpp>

namespace Flare::Render
{
	using namespace std;
	using namespace glm;
	using namespace Flare::Display;

	Renderer::Renderer(int width, int height) : camera{ width,height }, sortType{ GlyphSortType::NONE }, vertexBufferID{ 0 }, vertexArrayID{ 0 }{}

	Glyph& Renderer::next_glyph()
	{
		return this->glyphs_vial.next();
	}

	void Renderer::initialize()
	{
		this->colorProgram.compileShader("shader/vertex.shader", "shader/fragment.shader");
		this->colorProgram.addAttribute("vertexPosition");
		this->colorProgram.addAttribute("vertexColor");
		this->colorProgram.addAttribute("vertexUV");
		this->colorProgram.linkShader();
		this->createVertexArray();

		this->sprite_font.initialize("font/disney.ttf", 64);
	}

	void Renderer::begin(GlyphSortType sortType)
	{
		this->sortType = sortType;
		this->renderBatches.clear();
		this->glyphs_vial.refill();
	}

	void Renderer::end()
	{
		this->glyphs_pointers.resize(this->glyphs_vial.size());

		for (unsigned int i{ 0 }, const l{ this->glyphs_vial.size() }; i < l; ++i)
		{
			this->glyphs_pointers[i] = &this->glyphs_vial[i];
		}

		this->createRenderBatches();
	}


	void Renderer::render()
	{
		glBindVertexArray(this->vertexArrayID);

		for (auto& i : this->renderBatches)
		{
			glBindTexture(GL_TEXTURE_2D, i.texture);
			glDrawArrays(GL_TRIANGLES, i.offset, i.vertexCount);
		}

		glBindVertexArray(0);
	}

	void Renderer::renderNow()
	{
		this->camera.update();

		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->colorProgram.use();
		glActiveTexture(GL_TEXTURE0);

		auto textureLocation = this->colorProgram.getUniform("imageSampler");
		glUniform1i(textureLocation, 0);

		auto locationCamera = this->colorProgram.getUniform("cameraPosition");
		auto cameraMatrix = this->camera.getCameraMatrix();

		glUniformMatrix4fv(locationCamera, 1, GL_FALSE, &(cameraMatrix[0][0]));

		this->begin();


		for (auto& quad : this->stage.get_quads())
		{
			this->draw(quad.bound, quad.uv, quad.texture_id, 0.0f, Color{ 255,255,255,255 });
		}

		vector<Quad> quads = this->sprite_font.draw(this->text.c_str(), vec2(-400.0f, -200.0f), vec2(1.0f), 0.0f, Color{ 125,0,125,125 });

		for (auto& quad : quads)
		{
			this->draw(quad.bound, quad.uv, quad.texture_id, 0.0f, Color{ 255,255,255,255 });
		}

		this->end();
		this->render();

		glBindTexture(GL_TEXTURE_2D, 0);
		this->colorProgram.unuse();
	}

	void Renderer::createVertexArray()
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

	void Renderer::sortGlyphs()
	{
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

	void Renderer::createRenderBatches()
	{
		if (this->glyphs_pointers.empty())
		{
			return;
		}
		vector<Vertex> vertices{};
		vertices.resize(this->glyphs_pointers.size() * 6);

		auto glyph{ 0 };
		auto length{ this->glyphs_pointers.size() };
		auto offset{ 0 }, vertex{ 0 };
		GLuint previous_texture{ 0 };
		if (this->glyphs_vial.size() > 0)
		{
			do
			{
				if (this->glyphs_pointers.at(glyph)->texture != previous_texture)
				{
					this->renderBatches.emplace_back(offset, 6, this->glyphs_pointers.at(glyph)->texture);
				}
				else
				{
					this->renderBatches.back().vertexCount += 6;
				}
				vertices.at(vertex++) = this->glyphs_pointers.at(glyph)->down_left;
				vertices.at(vertex++) = this->glyphs_pointers.at(glyph)->top_left;
				vertices.at(vertex++) = this->glyphs_pointers.at(glyph)->top_right;
				vertices.at(vertex++) = this->glyphs_pointers.at(glyph)->top_right;
				vertices.at(vertex++) = this->glyphs_pointers.at(glyph)->down_right;
				vertices.at(vertex++) = this->glyphs_pointers.at(glyph)->down_left;
				offset += 6;
				previous_texture = this->glyphs_pointers.at(glyph)->texture;
			} while (++glyph < length);
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::draw(const glm::vec4 bound, const glm::vec4 uv, GLuint texture, float depth, const Color color)
	{
		Glyph& glyph = this->next_glyph();

		glyph.down_left.color = color;
		glyph.down_left.setPosition(bound.x, bound.y + bound.w);
		glyph.down_left.setUV(uv.x, uv.y + uv.w);

		glyph.top_left.color = color;
		glyph.top_left.setPosition(bound.x, bound.y);
		glyph.top_left.setUV(uv.x, uv.y);

		glyph.top_right.color = color;
		glyph.top_right.setPosition(bound.x + bound.z, bound.y);
		glyph.top_right.setUV(uv.x + uv.z, uv.y);

		glyph.down_right.color = color;
		glyph.down_right.setPosition(bound.x + bound.z, bound.y + bound.w);
		glyph.down_right.setUV(uv.x + uv.z, uv.y + uv.w);

		glyph.texture = texture;
	}

	bool Renderer::compareFrontBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}

	bool Renderer::compareBackFront(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}

	bool Renderer::compareTexture(Glyph* a, Glyph* b)
	{
		return a->texture > b->texture;
	}
}
