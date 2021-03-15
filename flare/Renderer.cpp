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
		this->vertex_buffer.refill();
		this->previous_texture = 0;
	}

	void Renderer::end()
	{
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

	void Renderer::createRenderBatches()
	{
		if (this->vertex_buffer.empty()) {
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);

		glBufferData(GL_ARRAY_BUFFER, this->vertex_buffer.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertex_buffer.size() * sizeof(Vertex), this->vertex_buffer.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::draw(const glm::vec4 bound, const glm::vec4 uv, GLuint texture, float depth, const Color color)
	{
		if (texture != this->previous_texture)
		{
			this->renderBatches.emplace_back(this->vertex_buffer.get_index(), 6, texture);
		}
		else
		{
			this->renderBatches.back().vertexCount += 6;
		}

		this->previous_texture = texture;

		const Vertex top_left{ Position{bound.x, bound.y}, color, UV{ uv.x, uv.y } };
		const Vertex top_right{ Position{bound.x + bound.z, bound.y}, color, UV{ uv.x + uv.z, uv.y } };
		const Vertex bottom_left{ Position{bound.x, bound.y + bound.w}, color, UV{uv.x, uv.y + uv.w } };
		const Vertex bottom_right{ Position{bound.x + bound.z, bound.y + bound.w}, color, UV{ uv.x + uv.z, uv.y + uv.w } };

		this->vertex_buffer.next() = bottom_left;
		this->vertex_buffer.next() = top_left;
		this->vertex_buffer.next() = top_right;
		this->vertex_buffer.next() = top_right;
		this->vertex_buffer.next() = bottom_right;
		this->vertex_buffer.next() = bottom_left;
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
