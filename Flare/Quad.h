#pragma once

#include <gl/glew.h>


class Quad
{
public:
	Quad(float x, float y, float width, float height);
	~Quad();

	void initialize();
	void draw();
	
private:
	GLuint vertextBufferID;

	float x, y, width, height;
};

