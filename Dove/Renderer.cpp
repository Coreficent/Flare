#include "Renderer.h"
#include <glm/detail/type_vec4.hpp>
#include <algorithm>
#include "ResourceManager.h"
#include "Display.h"
#include "mathematics.h"

using namespace std;

namespace Dove
{
	RenderBatch::RenderBatch()
	{
	}

	Renderer::Renderer(int width, int height):
		camera{width,height}, sortType{GlyphSortType::NONE}, vertexBufferID{0}, vertexArrayID{0}
	{
	}

	Renderer::~Renderer()
	{
	}
	/*
	Glyph& Renderer::next_glyph()
	{
		return this->glyphs_vial.next();
	}
	*/
	Glyph& Renderer::next_glyph(GLuint texture)
	{
		++this->glyph_count;
		return this->render_buffer[texture].next();
	}

	void Renderer::initialize()
	{
		this->colorProgram.compileShader("shader/colorShade.sv", "shader/colorShade.sf");
		this->colorProgram.addAttribute("vertexPosition");
		this->colorProgram.addAttribute("vertexColor");
		this->colorProgram.addAttribute("vertexUV");
		this->colorProgram.linkShader();
		this->createVertexArray();


		this->sprite_font.initialize("font/disney.ttf", 64);
	}

	void Renderer::begin(GlyphSortType sortType)
	{
		this->glyph_count = 0;
		this->sortType = sortType;
		//this->renderBatches.clear();
		this->render_baches.refill();

		for(auto& vial : this->render_buffer)
		{
			vial.second.refill();
		}
		//this->glyphs_vial.refill();
		//this->glyphs.clear();
		//this->glyphs_pointers.clear();
	}

	void Renderer::end()
	{
		//TODO temp delete comment

		/*
		this->glyphs_pointers.resize(this->glyphs_vial.size());
		for (unsigned int i{0}, l{ this->glyphs_vial.size() }; i < l; ++i)
		{
			this->glyphs_pointers[i] = &this->glyphs_vial[i];
		}
		*/
		//this->sortGlyphs();

		this->createRenderBatches();
	}


	void Renderer::render_batch()
	{
		glBindVertexArray(this->vertexArrayID);


		for(unsigned int i = 0, l = this->render_baches.size();i<l;++i)
		{
			glBindTexture(GL_TEXTURE_2D, this->render_baches[i].texture);
			glDrawArrays(GL_TRIANGLES, this->render_baches[i].offset, this->render_baches[i].vertexCount);
		}

		/*
		for (auto& i : this->renderBatches)
		{
			glBindTexture(GL_TEXTURE_2D, i.texture);
			glDrawArrays(GL_TRIANGLES, i.offset, i.vertexCount);
		}
		*/
		glBindVertexArray(0);
	}

	void Renderer::render()
	{
		this->camera.update();

		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->colorProgram.use();
		glActiveTexture(GL_TEXTURE0);

		auto textureLocation = this->colorProgram.getUniform("cakeSampler");
		glUniform1i(textureLocation, 0);

		// camera location
		auto locationCamera = this->colorProgram.getUniform("cameraPosition");
		auto cameraMatrix = this->camera.getCameraMatrix();

		glUniformMatrix4fv(locationCamera, 1, GL_FALSE, &(cameraMatrix[0][0]));

		this->begin();
		glm::vec4 position{0.0f,0.0f,50.0f,50.0f};
		glm::vec4 uv{0.0f,0.0f,1.0f,1.0f};
		static auto texture = ResourceManager::getTexture("texture/cake.png");
		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;
		Display display_object{};
		display_object.set_texture_id(texture.id);
		display_object.set_width(100.0f);
		display_object.set_height(100.0f);
		display_object.scale(2.0f);
		display_object.rotate(to_radian(0.0f));
		for (auto i{0}; i < 1500; ++i)
		{
			display_object.set_x(100.0f * i);
			display_object.render();
		}
		///////// stage renderer
		//this->stage.render();

		//////////


		this->sprite_font.draw(*this, "a b c d e f g \nh i j k l n m \no p q r s t \nu v w x y z", glm::vec2(1.0f), glm::vec2(1.0f), 0.0f, Color{125,0,125,125});

		// ouput sprite sheet
		//Glyph& glyph = this->next_glyph();
		Glyph& glyph = this->next_glyph(this->sprite_font._texID);

		glyph.top_left.color = color;
		glyph.top_left.setPosition(0.0f, 0.0f);
		glyph.top_left.setUV(0.0f, 0.0f);

		glyph.top_right.color = color;
		glyph.top_right.setPosition(500.0f, 0.0f);
		glyph.top_right.setUV(1.0f, 0.0f);

		glyph.down_left.color = color;
		glyph.down_left.setPosition(0.0f, 500.0f);
		glyph.down_left.setUV(0.0f, 1.0f);

		glyph.down_right.color = color;
		glyph.down_right.setPosition(500.0f, 500.0f);
		glyph.down_right.setUV(1.0f, 1.0f);

		glyph.texture = this->sprite_font._texID;

		////////// out put sprite sheet
		this->end();
		this->render_batch();

		//this->draw_text();

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
		//TODO use sort?
		/*
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
		*/
	}

	void Renderer::createRenderBatches()
	{
		/*
		if (this->glyphs_pointers.empty())
		{
			return;
		}
		vector<Vertex> vertices{};
		vertices.resize(this->glyphs_pointers.size() * 6);

		// TODO int size?

		unsigned long long glyph{0}, length{this->glyphs_pointers.size()};
		auto offset{0}, vertex{0};
		GLuint previous_texture{0};
		if (this->glyphs_vial.size() > 0)
		{
			do
			{
				if (this->glyphs_pointers[glyph]->texture != previous_texture)
				{
					//this->renderBatches.emplace_back(offset, 6, this->glyphs_pointers[glyph]->texture);
					auto& next = this->render_baches.next();
					next.offset = offset;
					next.vertexCount = 6;
					next.texture = this->glyphs_pointers[glyph]->texture;
				}
				else
				{
					//this->renderBatches.back().vertexCount += 6;
					this->render_baches[this->render_baches.size() - 1].vertexCount += 6;
				}
				vertices[vertex++] = this->glyphs_pointers[glyph]->down_left;
				vertices[vertex++] = this->glyphs_pointers[glyph]->top_left;
				vertices[vertex++] = this->glyphs_pointers[glyph]->top_right;
				vertices[vertex++] = this->glyphs_pointers[glyph]->top_right;
				vertices[vertex++] = this->glyphs_pointers[glyph]->down_right;
				vertices[vertex++] = this->glyphs_pointers[glyph]->down_left;
				offset += 6;
				previous_texture = this->glyphs_pointers[glyph]->texture;
			}
			while (++glyph < length);
		}
		*/

		
		auto offset_i{ 0 }, vertex{0};
		vector<Vertex> buffered_vertices{};
		buffered_vertices.resize(glyph_count * 6);
		/*
		
		
		for(auto& pair : this->render_buffer)
		{
			GLuint vertex_total{ 6 * pair.second.size() };
			auto& next = this->render_baches.next();
			next.offset = offset_i;
			next.vertexCount = vertex_total;
			next.texture = pair.first;
			
			for(unsigned int i{0},l{ pair.second.size()};i<l;++i)
			{
				auto& glyph_current = pair.second[i];
				buffered_vertices[vertex++] = glyph_current.down_left;
				buffered_vertices[vertex++] = glyph_current.top_left;
				buffered_vertices[vertex++] = glyph_current.top_right;
				buffered_vertices[vertex++] = glyph_current.top_right;
				buffered_vertices[vertex++] = glyph_current.down_right;
				buffered_vertices[vertex++] = glyph_current.down_left;
			}
			
			offset_i += vertex_total;
		}
		*/
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, buffered_vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, buffered_vertices.size() * sizeof(Vertex), buffered_vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::draw(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color)
	{
		//this->glyphs.emplace_back(bound, uv, texture, depth, color, 5*0.7853f);
		//Glyph& glyph = this->next_glyph();
		Glyph& glyph = this->next_glyph(texture);
		/**/
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
		//this->glyphs.push_back(glyph);
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
