#include "EPAAlgorithm.h"

using namespace NCL;
using namespace Maths;
using namespace CSC8503;

EPAAlgorithm::EPAAlgorithm()
{
}


EPAAlgorithm::~EPAAlgorithm()
{
}

void EPAAlgorithm::GetBestTriangle(std::list<EPATriangle>& list, EPATriangle& outTri, float& outDist) {
	std::list<EPATriangle>::iterator i = list.begin();

	float currentDist = Vector3::Dot(i->normal, i->a.pos);
	i++;

	while (i != list.end()) {
		float thisDist = Vector3::Dot(i->normal, i->a.pos);
		if (thisDist < currentDist) {
			outDist = thisDist;
			outTri = *i;
		}
		++i;
	}
}

void EPAAlgorithm::EPASimplexCalculator(Simplex& simplex, const OBBVolume& volumeA, const Transform& worldTransformA,
	const OBBVolume& volumeB, const Transform& worldTransformB, CollisionDetection::CollisionInfo& collisionInfo) {

	//std::list<EPATriangle>	tris;
	//std::list<EPAEdge>		edges;

	//tris.emplace_back(simplex.GetSupportPoint(0), simplex.GetSupportPoint(1), simplex.GetSupportPoint(2));
	//tris.emplace_back(simplex.GetSupportPoint(0), simplex.GetSupportPoint(2), simplex.GetSupportPoint(3));
	//tris.emplace_back(simplex.GetSupportPoint(0), simplex.GetSupportPoint(4), simplex.GetSupportPoint(1));
	//tris.emplace_back(simplex.GetSupportPoint(1), simplex.GetSupportPoint(4), simplex.GetSupportPoint(2));

	//const int MAX_EPA_ITERATIONS = 32;
	//int i = 0;

	//for (i = 0; i < MAX_EPA_ITERATIONS; ++i) {
	//	EPATriangle*t;
	//	float f = 0.0f;
	//	GetBestTriangle(tris, *t, f);

	//}
}