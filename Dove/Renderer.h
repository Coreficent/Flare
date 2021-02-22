#pragma once
#include <gl/glew.h>
#include "Vertex.h"
#include <vector>
#include "Glyph.h"
#include "GLSL.h"
#include "Camera.h"
#include "SpriteFont.h"
#include "Vial.h"
#include <unordered_map>

namespace Dove
{
	

	enum class GlyphSortType
	{
		NONE,
		FRONT_BACK,
		BACK_FRONT,
		TEXTURE
	};


	class RenderBatch
	{
	public:
		RenderBatch();
		RenderBatch(GLuint offset, GLuint vertexCount, GLuint texture) 
			: offset{offset}, vertexCount{vertexCount}, texture{texture}
		{
		}

		GLuint offset{0};
		GLuint vertexCount{0};
		GLuint texture{0};
	};

	class Renderer
	{
	public:
		Renderer(int width, int height);
		~Renderer();

		//Glyph& next_glyph();

		Glyph& next_glyph(GLuint texture);

		void initialize();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4& bound, const glm::vec4& uv, GLuint texture, float depth, const Color& color);
		void render_batch();

		void render();

		

		//TODO temp public //
		Camera camera;
		
	private:
		//TODO check for unused vairables

		void createVertexArray();
		void sortGlyphs();
		void createRenderBatches();

		static bool compareFrontBack(Glyph* a, Glyph* b);
		static bool compareBackFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		//std::vector<Glyph*> glyphs_pointers;

		std::unordered_map<GLuint,Vial<Glyph>> render_buffer{};
		unsigned int glyph_count{ 0 };


		Vial<RenderBatch> render_baches{};
		//Vial<Glyph> glyphs_vial{};


		GLSL colorProgram;


		

		SpriteFont sprite_font{};

		GlyphSortType sortType;

		GLuint vertexBufferID;
		GLuint vertexArrayID;

		//unsigned int glyph_id{0};
	};
}
