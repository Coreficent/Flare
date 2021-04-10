#pragma once

#ifndef Text_field_h__
#define Text_field_h__

#include "Quad.h"
#include "Vertex.h"
#include "Sprite.h"

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <ttf/SDL_ttf.h>
#include <vector>

namespace Flare
{
	using namespace Flare;
	using namespace glm;
	using namespace std;

	struct GLTexture;

	struct CharGlyph
	{
		char character;
		vec4 uvRect;
		vec2 size;
	};

	/// For text justification
	enum class Justification
	{
		LEFT,
		MIDDLE,
		RIGHT
	};

	class Text_field : public Sprite
	{

	public:

		Text_field(string font, int size);

		/// Destroys the font resources
		void dispose();

		/// Measures the dimensions of the text
		vec2 measure(const char* s);

		unsigned int _texID;

		/// Draws using a QuadBatch

		vector<Quad> graphics() override;

		string text{};

	private:
		static vector<vector<int>> create_rows(ivec4* rects, int rectsLength, int r, int padding, int& w);

		int closestPow2(int i);

		int font_start, font_length;
		CharGlyph* _glyphs;
		int font_height;

		int maximum_resolution{ 4096 };
	};
}

#endif
