#include "Quad.h"
#include "Renderer.h"
#include "Resource_manager.h"
#include "Sprite.h"
#include "debug.h"
#include "mathematics.h"

#include <algorithm>
#include <glm/detail/type_vec4.hpp>

namespace Flare
{
	using namespace std;
	using namespace glm;
	using namespace Flare;

	Renderer::Renderer(int width, int height) : camera{ width,height }, vertex_buffer_id{ 0 }, vertex_array_id{ 0 }{}

	void Renderer::initialize()
	{
		this->color_program.compile_shader("shader/vertex.shader", "shader/fragment.shader");
		this->color_program.add_attribute("vertexPosition");
		this->color_program.add_attribute("vertexColor");
		this->color_program.add_attribute("vertexUV");
		this->color_program.link_shader();
		this->create_vertex_array();
	}

	void Renderer::begin()
	{
		this->draw_call_count = 0;

		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->color_program.use();
		glActiveTexture(GL_TEXTURE0);

		auto textureLocation = this->color_program.get_uniform("imageSampler");
		glUniform1i(textureLocation, 0);

		auto local_camera = this->color_program.get_uniform("cameraPosition");
		auto camera_matrix = this->camera.get_camera_matrix();

		glUniformMatrix4fv(local_camera, 1, GL_FALSE, &(camera_matrix[0][0]));

		this->render_batches.clear();
		this->vertex_buffer.refill();
		this->previous_texture = 8192;
	}

	void Renderer::end()
	{
		this->generate_batches();
	}

	void Renderer::finalize() noexcept
	{
		glBindVertexArray(this->vertex_array_id);

		for (auto& i : this->render_batches)
		{
			glBindTexture(GL_TEXTURE_2D, i.texture);
			glDrawArrays(GL_TRIANGLES, i.offset, i.vertex_count);
		}

		glBindVertexArray(0);
	}

	void Renderer::render(Sprite& stage)
	{
		this->camera.update();

		this->begin();

		this->draw(stage.graphics());

		this->end();
		this->finalize();

		glBindTexture(GL_TEXTURE_2D, 0);
		this->color_program.unuse();
	}

	void Renderer::create_vertex_array() noexcept
	{
		if (!this->vertex_array_id)
		{
			glGenVertexArrays(1, &this->vertex_array_id);
		}

		glBindVertexArray(this->vertex_array_id);

		if (!this->vertex_buffer_id)
		{
			glGenBuffers(1, &this->vertex_buffer_id);
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_id);

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

	void Renderer::generate_batches()
	{
		if (this->vertex_buffer.empty()) {
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_id);

		glBufferData(GL_ARRAY_BUFFER, this->vertex_buffer.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertex_buffer.size() * sizeof(Vertex), this->vertex_buffer.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::draw(const vector<Quad>& quads) {
		for (auto& quad : quads)
		{
			this->draw(quad);
		}
	}

	void Renderer::draw(const Quad& quad) {
		this->draw(quad, quad.uv, quad.texture_id, 0.0f, Color{ 255,255,255,255 });
	}

	void Renderer::draw(const Quad& quad, const vec4 uv, GLuint texture, float depth, const Color color)
	{
		if (texture != this->previous_texture)
		{
			this->render_batches.emplace_back(this->vertex_buffer.get_index(), 6, texture);
			++this->draw_call_count;
		}
		else
		{
			this->render_batches.back().vertex_count += 6;
		}

		this->previous_texture = texture;

		const Vertex top_left{ quad.top_left, color, UV{ uv.x, uv.y } };
		const Vertex top_right{ quad.top_right, color, UV{ uv.x + uv.z, uv.y } };
		const Vertex bottom_left{ quad.bottom_left, color, UV{uv.x, uv.y + uv.w } };
		const Vertex bottom_right{ quad.bottom_right, color, UV{ uv.x + uv.z, uv.y + uv.w } };

		this->vertex_buffer.next() = bottom_left;
		this->vertex_buffer.next() = top_left;
		this->vertex_buffer.next() = top_right;
		this->vertex_buffer.next() = top_right;
		this->vertex_buffer.next() = bottom_right;
		this->vertex_buffer.next() = bottom_left;
	}
}
