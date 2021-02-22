#include "Matrix.h"

namespace Flare
{
	Matrix::Matrix()
	{
	}


	Matrix::~Matrix()
	{
	}

	void Matrix::translate(float x, float y)
	{
		this->x += x;
		this->y += y;
	}
}
