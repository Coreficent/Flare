#include "Quad.h"
#include <vector>
#include <cstddef>
#include "Vertex.h"

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
	
	vertexData[0].setPosition(topRightX, topRightY);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(topLeftX, topLeftY);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPosition(bottomLeftX, bottomLeftY);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].setPosition(bottomLeftX, bottomLeftY);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(bottomRightX, bottomRightY);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(topRightX, topRightY);
	vertexData[5].setUV(1.0f, 1.0f);

	for (auto& i : vertexData )
	{
		i.setColor(255, 255, 255, 255);
	}

	vertexData[1].setColor(0, 0, 255, 255);
	//vertexData[5].setColor(255, 0, 0, 255);


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
	//for texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));


	glDrawArrays(GL_TRIANGLES,0,6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}