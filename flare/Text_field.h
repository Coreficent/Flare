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
	using namespace std;
	using namespace Flare;

	struct GLTexture;

	struct CharGlyph
	{
		char character;
		glm::vec4 uvRect;
		glm::vec2 size;
	};

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

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

		Text_field(const char* font, int size);

		/// Destroys the font resources
		void dispose();

		int getFontHeight() const
		{
			return _fontHeight;
		}

		/// Measures the dimensions of the text
		glm::vec2 measure(const char* s);

		unsigned int _texID;

		/// Draws using a QuadBatch

		vector<Quad> graphics() override;

		string text{};

	private:
		static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);

		std::vector<Quad> draw(const char* s, glm::vec2 position, glm::vec2 scaling, float depth, Color tint, Justification just = Justification::LEFT);

		int _regStart, _regLength;
		CharGlyph* _glyphs;
		int _fontHeight;
	};
}

#endif // Text_field_h__
