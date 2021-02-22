#pragma once
#include <gl/glew.h>
#include "Vial.h"
#include "Vertex.h"

namespace Dove
{
	class Batch
	{
	public:
		Batch();
		~Batch();

		void begin();
		void draw(Vertex vertex);
		void end() const;
		void render() const;
		//TODO temp public
		GLuint texture{ 0 };
	private:

		Vial <Vertex> vertices{};

		GLuint buffer_id{0};

	};

}
