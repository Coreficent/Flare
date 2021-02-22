#include "Quad.h"
#include <vector>
#include <cstddef>
#include "Vertext.h"

using namespace std;

Quad::Quad(float x, float y, float width, float height):vertextBufferID{0},x{x},y{y},width{width},height{height}
{
}


Quad::~Quad()
{
	if(this->vertextBufferID)
	{
		glDeleteBuffers(1,&this->vertextBufferID);
	}
}


void Quad::initialize()
{
	if(!this->vertextBufferID)
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


	vector<Vertex> vertexData(6);

	//First Triangle
	vertexData[0].position.x = topRightX;
	vertexData[0].position.y = topRightY;

	vertexData[1].position.x = topLeftX;
	vertexData[1].position.y = topLeftY;

	vertexData[2].position.x = bottomLeftX;
	vertexData[2].position.y = bottomLeftY;

	//Second Triangle
	vertexData[3].position.x = bottomLeftX;
	vertexData[3].position.y = bottomLeftY;

	vertexData[4].position.x = topRightX;
	vertexData[4].position.y = topRightY;

	vertexData[5].position.x = bottomRightX;
	vertexData[5].position.y = bottomRightY;

	for (auto& i : vertexData )
	{
		i.color.r = 0;
		i.color.g = 255;
		i.color.b = 0;
		i.color.a = 255;
	}

	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;

	vertexData[5].color.g = 0;
	vertexData[5].color.r = 255;


	glBindBuffer(GL_ARRAY_BUFFER,this->vertextBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Quad::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertextBufferID);

	glEnableVertexAttribArray(0);

	//for position
	glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,position)));
	//for color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));


	glDrawArrays(GL_TRIANGLES,0,6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}