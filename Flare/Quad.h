#pragma once

#include <gl/glew.h>
#include "GlTexture.h"
#include <string>

using namespace std;

class Quad
{
public:
	Quad(float x, float y, float width, float height);
	~Quad();

	void initialize(string texturePath);
	void draw();
	
private:
	GLTexture quadTexture;

	GLuint vertextBufferID;

	float x, y, width, height;

	
};

