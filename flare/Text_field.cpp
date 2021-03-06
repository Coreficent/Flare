#include "Quad.h"
#include "Text_field.h"

#include <glm/gtc/matrix_transform.inl>
#include <iostream>
#include <sdl/SDL.h>

namespace Flare
{
	using namespace Flare;
	using namespace glm;
	using namespace std;

	Text_field::Text_field(string font, int size)
	{
		constexpr char first_printable_character{ 32 };
		constexpr char last_printable_character{ 126 };

		if (!TTF_WasInit())
		{
			TTF_Init();
		}

		TTF_Font* open_font = TTF_OpenFont(font.c_str(), size);

		if (!open_font)
		{
			cerr << "failed to open TTF font %s\n" << font << endl;
			throw 281;
		}

		font_height = TTF_FontHeight(open_font);
		font_start = first_printable_character;
		font_length = last_printable_character - first_printable_character + 1;

		const int padding = size / 8;

		// calculate regions

		vector<ivec4> rectangles(font_length);

		int i{ 0 };
		int advance{ 0 };

		for (char c = first_printable_character; c <= last_printable_character; ++c)
		{
			TTF_GlyphMetrics(open_font, c, &rectangles.at(i).x, &rectangles.at(i).z, &rectangles.at(i).y, &rectangles.at(i).w, &advance);
			rectangles.at(i).z -= rectangles.at(i).x;
			rectangles.at(i).x = 0;
			rectangles.at(i).w -= rectangles.at(i).y;
			rectangles.at(i).y = 0;
			++i;
		}

		// calculate partitions

		int rows{ 1 };
		int width{ 0 };
		int height{ 0 };
		int best_width{ 0 };
		int best_height{ 0 };
		int area{ this->maximum_resolution * this->maximum_resolution };
		int best_row = { 0 };

		vector<vector<int>> best_partition{};

		while (rows <= font_length)
		{
			height = rows * (padding + font_height) + padding;
			vector<vector<int>> created_rows = create_rows(rectangles, font_length, rows, padding, width);

			// Desire a power of 2 texture
			width = closestPow2(width);
			height = closestPow2(height);

			// A texture must be feasible
			if (width > this->maximum_resolution || height > this->maximum_resolution)
			{
				rows++;
				continue;
			}

			// Check for minimal area
			if (area >= width * height)
			{
				best_partition = created_rows;
				best_width = width;
				best_height = height;
				best_row = rows;
				area = best_width * best_height;
				rows++;
			}
			else
			{
				break;
			}
		}

		// Can a bitmap font be made?
		if (best_partition.empty())
		{
			cerr << "Failed to Map TTF font %s to texture. Try lowering resolution.\n" << font << endl;
			throw 282;
		}

		// Create the texture
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, best_width, best_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// Now draw all the glyphs
		SDL_Color color{ 255, 255, 255, 255 };
		int ly = padding;
		for (int ri = 0; ri < best_row; ri++)
		{
			int lx = padding;
			for (int ci = 0; ci < best_partition.at(ri).size(); ci++)
			{
				const int glyph_index = best_partition.at(ri).at(ci);

				SDL_Surface* glyphSurface = TTF_RenderGlyph_Blended(open_font, first_printable_character + glyph_index, color);

				// Save glyph image and update coordinates
				glTexSubImage2D(GL_TEXTURE_2D, 0, lx, ly, glyphSurface->w, glyphSurface->h, GL_BGRA, GL_UNSIGNED_BYTE, glyphSurface->pixels);
				rectangles.at(glyph_index).x = lx;
				rectangles.at(glyph_index).y = ly;
				rectangles.at(glyph_index).z = glyphSurface->w;
				rectangles.at(glyph_index).w = glyphSurface->h;

				SDL_FreeSurface(glyphSurface);
				glyphSurface = nullptr;

				lx += rectangles.at(glyph_index).z + padding;
			}
			ly += font_height + padding;
		}

		// Draw the unsupported glyph
		const int rs{ padding - 1 };
		const long white_size{ rs * rs };
		vector<int> white_squares(white_size);

		memset(white_squares.data(), 0xffffffff, white_size * sizeof(int));
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rs, rs, GL_RGBA, GL_UNSIGNED_BYTE, white_squares.data());

		// Set some texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Create QuadBatch glyphs
		const long glyph_size{ font_length + 1 };
		glyphs = vector< CharGlyph>(glyph_size);

		for (i = 0; i < font_length; i++)
		{
			glyphs.at(i).character = first_printable_character + i;
			glyphs.at(i).size = vec2(rectangles.at(i).z, rectangles.at(i).w);
			glyphs.at(i).uvRect = vec4{ 1.0f * rectangles.at(i).x / best_width,1.0f * rectangles.at(i).y / best_height,		1.0f * rectangles.at(i).z / best_width,	1.0f * rectangles.at(i).w / best_height };
		}

		glyphs.at(font_length).character = ' ';
		glyphs.at(font_length).size = glyphs.at(0).size;
		glyphs.at(font_length).uvRect = vec4(0, 0, 1.0f * rs / best_width, 1.0f * rs / best_height);

		glBindTexture(GL_TEXTURE_2D, 0);
		TTF_CloseFont(open_font);
	}

	void Text_field::dispose() noexcept
	{
		if (texture_id != 0)
		{
			glDeleteTextures(1, &texture_id);
			texture_id = 0;
		}
	}

	vector<vector<int>> Text_field::create_rows(vector<ivec4> rects, int rectsLength, int r, int padding, int& w)
	{
		// Blank initialize
		vector<vector<int>> result(r);

		vector<int> cw(r);
		for (int i = 0; i < r; i++)
		{
			cw.at(i) = padding;
		}

		// Loop through all glyphs
		for (int i = 0; i < rectsLength; i++)
		{
			// Find row for placement
			int ri = 0;
			for (int rii = 1; rii < r; rii++)
				if (cw.at(rii) < cw.at(ri)) ri = rii;

			// Add width to that row
			cw.at(ri) += rects.at(i).z + padding;

			// Add glyph to the row list
			result.at(ri).push_back(i);
		}

		// Find the max width
		w = 0;
		for (int i = 0; i < r; i++)
		{
			if (cw.at(i) > w) w = cw.at(i);
		}

		return result;
	}

	vec2 Text_field::measure(string s)
	{
		vec2 size(0, font_height);
		float cw = 0;

		for (const char c : s) {
			if (c == '\n')
			{
				size.y += font_height;
				if (size.x < cw)
				{
					size.x = cw;
				}
				cw = 0;
			}
			else
			{
				// Check for correct glyph
				int gi = c - font_start;
				if (gi < 0 || gi >= font_length)
				{
					gi = font_length;

				}
				cw += glyphs.at(gi).size.x;
			}
		}

		if (size.x < cw)
		{
			size.x = cw;
		}
		return size;
	}

	int Text_field::closestPow2(int i) noexcept
	{
		i--;
		int pi = 1;
		while (i > 0)
		{
			i >>= 1;
			pi <<= 1;
		}
		return pi;
	}

	vector<Quad> Text_field::graphics()
	{
		const Justification just{ Justification::LEFT };

		vector<Quad> result{};

		const vec2 position{};
		const vec2 scaling{ 1.0f, 1.0f };
		vec2 text_position = position;

		// Apply justification
		if (just == Justification::MIDDLE)
		{
			text_position.x -= measure(this->text).x * scaling.x / 2;
		}
		else if (just == Justification::RIGHT)
		{
			text_position.x -= measure(this->text).x * scaling.x;
		}

		for (const char c : this->text)
		{
			if (c == '\n')
			{
				text_position.y += font_height * scaling.y;
				text_position.x = position.x;
			}
			else
			{
				// Check for correct glyph
				int gi = c - font_start;

				if (gi < 0 || gi >= font_length)
				{
					gi = font_length;
				}

				const vec4 destRect(text_position, glyphs.at(gi).size * scaling);
				const vec4 uv = glyphs.at(gi).uvRect;

				vec3 top_left{ destRect.x, destRect.y, 1.0f };
				vec3 top_right{ destRect.x + destRect.z, destRect.y, 1.0f };
				vec3 bottom_left{ destRect.x,destRect.y + destRect.w, 1.0f };
				vec3 bottom_right{ destRect.x + destRect.z, destRect.y + destRect.w, 1.0f };

				const mat3 transform = this->calculate_matrix();

				top_left = transform * top_left;
				top_right = transform * top_right;
				bottom_left = transform * bottom_left;
				bottom_right = transform * bottom_right;

				result.push_back(Quad{ texture_id, Position{top_left.x, top_left.y}, Position{top_right.x, top_right.y}, Position{bottom_left.x, bottom_left.y}, Position{bottom_right.x, bottom_right.y}, uv });

				text_position.x += glyphs.at(gi).size.x * scaling.x;
			}
		}

		return result;
	}
}
