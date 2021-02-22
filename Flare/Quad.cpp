#include "Quad.h"
#include <vector>

using namespace std;

Quad::Quad(float x, float y, float width, float height):x{x},y{y},width{width},height{height},vertextBufferID{0}
{
}


Quad::~Quad()
{
	if(this->vertextBufferID!=0)
	{
		glDeleteBuffers(1,&this->vertextBufferID);
	}
}


void Quad::initialize()
{
	if(this->vertextBufferID==0)
	{
		glGenBuffers(1,&this->vertextBufferID);
	}
	
	float topLeftX = this->x;
	float topLeftY = this->y + this->height;
	float topRightX = this->x+this->width;
	float topRightY = this->y + this->height;
	float bottomLeftX = this->x;
	float bottomLeftY = this->y;
	float bottomRightX = this->x + this->width;
	float bottomRightY = this->y;


	vector<float> vertexData(12);

	//First Triangle
	vertexData[0] = topRightX;
	vertexData[1] = topRightY;

	vertexData[2] = topLeftX;
	vertexData[3] = topLeftY;

	vertexData[4] = bottomLeftX;
	vertexData[5] = bottomLeftY;

	//Second Triangle
	vertexData[6] = bottomLeftX;
	vertexData[7] = bottomLeftY;

	vertexData[8] = topRightX;
	vertexData[9] = topRightY;

	vertexData[10] = bottomRightX;
	vertexData[11] = bottomRightY;

	glBindBuffer(GL_ARRAY_BUFFER,this->vertextBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Quad::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertextBufferID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,nullptr);

	glDrawArrays(GL_TRIANGLES,0,6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}