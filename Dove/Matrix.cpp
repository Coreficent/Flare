#include "Matrix.h"

namespace Dove {

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