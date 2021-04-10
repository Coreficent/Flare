/*
This is a modified version of the Text_field class from the
Seed Of Andromeda source code.
Use it for any of your projects, commercial or otherwise,
free of charge, but do not remove this disclaimer.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

November 28 2014
Original Author: Cristian Zaloj
Modified By: Benjamin Arnold
*/

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
		Text_field();
		Text_field(const char* font, int size, char cs, char ce);

		Text_field(const char* font, int size) :
			Text_field(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR)
		{
		}

		void initialize(const char* font, int size);
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
		
		virtual vector<Quad> graphics() override;

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
