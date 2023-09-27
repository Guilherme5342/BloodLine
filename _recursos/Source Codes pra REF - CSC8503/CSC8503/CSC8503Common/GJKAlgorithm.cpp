#include "GJKAlgorithm.h"
#include "Simplex.h"
#include "../../Common/Vector3.h"
#include "Transform.h"
#include "Debug.h"
using namespace NCL;
using namespace Maths;
using namespace CSC8503;

bool GJKAlgorithm::GJKInserectionOBB(const NCL::OBBVolume& volumeA, const Transform& worldTransformA,
	const NCL::OBBVolume& volumeB, const Transform& worldTransformB, CollisionDetection::CollisionInfo& collisionInfo, float expansion) {
	return false;
}

Maths::Simplex::SupportPoint GJKAlgorithm::MinkowskiSupport(const Transform& worldTransformA, const Transform& worldTransformB, Vector3 aLocalDir, Vector3 bLocalDir, Vector3 expansion) {
	Maths::Simplex::SupportPoint point;
	
	return point;
}

Vector3 GJKAlgorithm::OBBSupport(const Transform& worldTransformA, Vector3 aLocalDir, Vector3 expansion) {
	return Vector3();
}

Vector3 GJKAlgorithm::CheckTriangleSimplex(Simplex &s, bool checkAbove) {
	return Vector3();
}
//returns true if this has been reduced to a triangle case
bool GJKAlgorithm::CheckTetrahedronSimplex(Simplex &s) {
	return false;
}