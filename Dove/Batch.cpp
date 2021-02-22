#include "Batch.h"


namespace Dove
{
	Batch::Batch()
	{
		//glGenVertexArrays(1, &this->array_id);
		//glBindVertexArray(this->array_id);

		//glGenBuffers(1, &this->buffer_id);
		//glBindBuffer(GL_ARRAY_BUFFER, this->buffer_id);


	}


	Batch::~Batch()
	{
		//glBindBuffer(GL_ARRAY_BUFFER, this->buffer_id);
		//glDeleteBuffers(1, &this->buffer_id);
	}

	void Batch::begin()
	{
		this->vertices.clear();
	}

	void Batch::draw(Vertex vertex)
	{
		this->vertices.push_back(vertex);
	}

	void Batch::end() const
	{
		//glBindBuffer(GL_ARRAY_BUFFER, this->buffer_id);
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Batch::render() const
	{
		//glBindTexture(GL_TEXTURE_2D, this->texture);
		//glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	}
}
