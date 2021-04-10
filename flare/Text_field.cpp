#include "Text_field.h"
#include "Quad.h"
#include <sdl/SDL.h>
#include <glm/gtc/matrix_transform.inl>
#include <iostream>


int closestPow2(int i)
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

#define MAX_TEXTURE_RES 4096

namespace Flare
{
	using namespace Flare;

	Text_field::Text_field(const char* font, int size)
	{
		char cs = FIRST_PRINTABLE_CHAR;
		char ce = LAST_PRINTABLE_CHAR;
		// Initialize SDL_ttf
		if (!TTF_WasInit())
		{
			TTF_Init();
		}
		TTF_Font* f = TTF_OpenFont(font, size);
		if (f == nullptr)
		{
			fprintf(stderr, "Failed to open TTF font %s\n", font);
			fflush(stderr);
			throw 281;
		}
		_fontHeight = TTF_FontHeight(f);
		_regStart = cs;
		_regLength = ce - cs + 1;
		int padding = size / 8;

		// First neasure all the regions
		glm::ivec4* glyphRects = new glm::ivec4[_regLength];
		int i = 0, advance;
		for (char c = cs; c <= ce; c++)
		{
			TTF_GlyphMetrics(f, c, &glyphRects[i].x, &glyphRects[i].z, &glyphRects[i].y, &glyphRects[i].w, &advance);
			glyphRects[i].z -= glyphRects[i].x;
			glyphRects[i].x = 0;
			glyphRects[i].w -= glyphRects[i].y;
			glyphRects[i].y = 0;
			i++;
		}

		// Find best partitioning of glyphs
		int rows = 1, w, h, bestWidth = 0, bestHeight = 0, area = MAX_TEXTURE_RES * MAX_TEXTURE_RES, bestRows = 0;
		std::vector<int>* bestPartition = nullptr;
		while (rows <= _regLength)
		{
			h = rows * (padding + _fontHeight) + padding;
			auto gr = createRows(glyphRects, _regLength, rows, padding, w);

			// Desire a power of 2 texture
			w = closestPow2(w);
			h = closestPow2(h);

			// A texture must be feasible
			if (w > MAX_TEXTURE_RES || h > MAX_TEXTURE_RES)
			{
				rows++;
				delete[] gr;
				continue;
			}

			// Check for minimal area
			if (area >= w * h)
			{
				if (bestPartition) delete[] bestPartition;
				bestPartition = gr;
				bestWidth = w;
				bestHeight = h;
				bestRows = rows;
				area = bestWidth * bestHeight;
				rows++;
			}
			else
			{
				delete[] gr;
				break;
			}
		}

		// Can a bitmap font be made?
		if (!bestPartition)
		{
			fprintf(stderr, "Failed to Map TTF font %s to texture. Try lowering resolution.\n", font);
			fflush(stderr);
			throw 282;
		}
		// Create the texture
		glGenTextures(1, &_texID);
		glBindTexture(GL_TEXTURE_2D, _texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bestWidth, bestHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// Now draw all the glyphs
		SDL_Color fg = { 255, 255, 255, 255 };
		int ly = padding;
		for (int ri = 0; ri < bestRows; ri++)
		{
			int lx = padding;
			for (int ci = 0; ci < bestPartition[ri].size(); ci++)
			{
				int gi = bestPartition[ri][ci];

				SDL_Surface* glyphSurface = TTF_RenderGlyph_Blended(f, (char)(cs + gi), fg);

				// Pre-multiplication occurs here
				unsigned char* sp = (unsigned char*)glyphSurface->pixels;
				int cp = glyphSurface->w * glyphSurface->h * 4;
				for (int i = 0; i < cp; i += 4)
				{
					sp[i] *= sp[i + 3] / 255;
					sp[i + 1] = sp[i];
					sp[i + 2] = sp[i];
				}

				// Save glyph image and update coordinates
				glTexSubImage2D(GL_TEXTURE_2D, 0, lx, ly, glyphSurface->w, glyphSurface->h, GL_BGRA, GL_UNSIGNED_BYTE, glyphSurface->pixels);
				glyphRects[gi].x = lx;
				glyphRects[gi].y = ly;
				glyphRects[gi].z = glyphSurface->w;
				glyphRects[gi].w = glyphSurface->h;

				SDL_FreeSurface(glyphSurface);
				glyphSurface = nullptr;

				lx += glyphRects[gi].z + padding;
			}
			ly += _fontHeight + padding;
		}

		// Draw the unsupported glyph
		int rs = padding - 1;
		int* pureWhiteSquare = new int[rs * rs];
		memset(pureWhiteSquare, 0xffffffff, rs * rs * sizeof(int));
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rs, rs, GL_RGBA, GL_UNSIGNED_BYTE, pureWhiteSquare);
		delete[] pureWhiteSquare;
		pureWhiteSquare = nullptr;

		// Set some texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Create QuadBatch glyphs
		_glyphs = new CharGlyph[_regLength + 1];
		for (i = 0; i < _regLength; i++)
		{
			_glyphs[i].character = (char)(cs + i);
			_glyphs[i].size = glm::vec2(glyphRects[i].z, glyphRects[i].w);
			_glyphs[i].uvRect = glm::vec4(
				(float)glyphRects[i].x / (float)bestWidth,
				(float)glyphRects[i].y / (float)bestHeight,
				(float)glyphRects[i].z / (float)bestWidth,
				(float)glyphRects[i].w / (float)bestHeight
			);
		}
		_glyphs[_regLength].character = ' ';
		_glyphs[_regLength].size = _glyphs[0].size;
		_glyphs[_regLength].uvRect = glm::vec4(0, 0, (float)rs / (float)bestWidth, (float)rs / (float)bestHeight);

		glBindTexture(GL_TEXTURE_2D, 0);
		delete[] glyphRects;
		delete[] bestPartition;
		TTF_CloseFont(f);
	}

	void Text_field::dispose()
	{
		if (_texID != 0)
		{
			glDeleteTextures(1, &_texID);
			_texID = 0;
		}
		if (_glyphs)
		{
			delete[] _glyphs;
			_glyphs = nullptr;
		}
	}

	std::vector<int>* Text_field::createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w)
	{
		// Blank initialize
		std::vector<int>* l = new std::vector<int>[r]();
		int* cw = new int[r]();
		for (int i = 0; i < r; i++)
		{
			cw[i] = padding;
		}

		// Loop through all glyphs
		for (int i = 0; i < rectsLength; i++)
		{
			// Find row for placement
			int ri = 0;
			for (int rii = 1; rii < r; rii++)
				if (cw[rii] < cw[ri]) ri = rii;

			// Add width to that row
			cw[ri] += rects[i].z + padding;

			// Add glyph to the row list
			l[ri].push_back(i);
		}

		// Find the max width
		w = 0;
		for (int i = 0; i < r; i++)
		{
			if (cw[i] > w) w = cw[i];
		}

		return l;
	}

	glm::vec2 Text_field::measure(const char* s)
	{
		glm::vec2 size(0, _fontHeight);
		float cw = 0;
		for (int si = 0; s[si] != 0; si++)
		{
			char c = s[si];
			if (s[si] == '\n')
			{
				size.y += _fontHeight;
				if (size.x < cw)
					size.x = cw;
				cw = 0;
			}
			else
			{
				// Check for correct glyph
				int gi = c - _regStart;
				if (gi < 0 || gi >= _regLength)
					gi = _regLength;
				cw += _glyphs[gi].size.x;
			}
		}
		if (size.x < cw)
			size.x = cw;
		return size;
	}

	std::vector<Quad> Text_field::draw(const char* s, glm::vec2 position, glm::vec2 scaling, float depth, Color tint, Justification just /* = Justification::LEFT */)
	{
		std::vector<Quad> result{};

		glm::vec2 tp = position;
		// Apply justification
		if (just == Justification::MIDDLE)
		{
			tp.x -= measure(s).x * scaling.x / 2;
		}
		else if (just == Justification::RIGHT)
		{
			tp.x -= measure(s).x * scaling.x;
		}
		for (int si = 0; s[si] != 0; si++)
		{
			char c = s[si];
			if (s[si] == '\n')
			{
				tp.y += _fontHeight * scaling.y;

				tp.x = position.x;
			}
			else
			{
				// Check for correct glyph
				int gi = c - _regStart;
				if (gi < 0 || gi >= _regLength)
					gi = _regLength;
				glm::vec4 destRect(tp, _glyphs[gi].size * scaling);
				glm::vec4 uv = _glyphs[gi].uvRect;

				//TODO implement render for text

				// batch.draw(destRect, uv, _texID, depth, tint);

				//result.push_back(destRect);
				//result.push_back(uv);


				result.push_back(Quad{ _texID, destRect ,uv });

				tp.x += _glyphs[gi].size.x * scaling.x;
			}
		}

		return result;
	}

	vector<Quad> Text_field::graphics()
	{
		return this->draw(this->text.c_str(), vec2(-400.0f, -200.0f), vec2(1.0f), 0.0f, Color{ 125,0,125,125 });
	}
}
