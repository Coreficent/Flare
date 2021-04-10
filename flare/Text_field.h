#pragma once

#ifndef Text_field_h__
#define Text_field_h__

#include "Quad.h"
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
		char character{};
		vec4 uvRect{};
		vec2 size{};
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
		void dispose() noexcept;

		/// Measures the dimensions of the text
		vec2 measure(string s);

		unsigned int texture_id;

		vector<Quad> graphics() override;

		string text{};

	private:

		vector<CharGlyph> glyphs;

		int font_start;
		int font_length;
		int font_height;
		int maximum_resolution{ 4096 };

		static vector<vector<int>> create_rows(vector<ivec4> rects, int rectsLength, int r, int padding, int& w);
		int closestPow2(int i) noexcept;
	};
}

#endif
