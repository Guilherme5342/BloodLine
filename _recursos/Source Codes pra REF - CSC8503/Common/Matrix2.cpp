#include "Matrix2.h"
#include "Maths.h"

using namespace NCL;
using namespace NCL::Maths;

Matrix2::Matrix2(void)	{
	values[0] = 1.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 1.0f;
}

Matrix2::~Matrix2(void)	{
}

void Matrix2::ToZero() {
	values[0] = 0.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 0.0f;
}

void Matrix2::ToIdentity() {
	values[0] = 1.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 1.0f;
}

Matrix2 Matrix2::Rotation(float degrees)	{
	Matrix2 mat;

	float radians = Maths::DegreesToRadians(degrees);
	float s = sin(radians);
	float c = cos(radians);

	mat.values[0] = c;
	mat.values[1] = s;
	mat.values[2] = -s;
	mat.values[3] = c;

	return mat;
}