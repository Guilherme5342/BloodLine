#include "Simplex.h"
#include "Debug.h"
using namespace NCL::Maths;

Simplex::Simplex()	{
	index = 0;
	size  = 0;
}

Simplex::~Simplex()	{
}

void Simplex::SetToTri(SupportPoint a, SupportPoint b, SupportPoint c) {
	verts[0]	= a;
	verts[1]	= b;
	verts[2]	= c;
	index		= 3;
	size		= 3;
}

void Simplex::SetToLine(SupportPoint a, SupportPoint b) {
	verts[0] = a;
	verts[1] = b;
	index	= 2;
	size	= 2;
}

void Simplex::Add(SupportPoint a) {
	verts[index]	= a;
	index			= (index + 1) % 4;
	size++;
}

void Simplex::RemoveOldestSupportPoint() {
	size--;
}

float Simplex::GetClosestDistance() {
	return 0;
}

Vector3 Simplex::ReduceToClosestSimplex() {
	return Vector3();
}