#pragma once
#include "Simplex.h"
#include "CollisionDetection.h"
#include "OBBVolume.h"
namespace NCL {
	class OBBVolume;
	namespace Maths {
		class Simplex;
	}
	namespace CSC8503 {
		class Transform;
		
		class Maths::Vector3;
		class GJKAlgorithm	{
		public:
			static bool GJKInserectionOBB(
				const NCL::OBBVolume& volumeA, const Transform& worldTransformA,
				const NCL::OBBVolume& volumeB, const Transform& worldTransformB, 
				CollisionDetection::CollisionInfo& collisionInfo, float expansion = 1.0f);

		private:			
			static Maths::Simplex::SupportPoint MinkowskiSupport(
				const Transform& worldTransformA, const Transform& worldTransformB,
				Maths::Vector3 aLocalDir, Maths::Vector3 bLocalDir, Vector3 expansion = Vector3(0, 0, 0));
	
			static Vector3 OBBSupport(
				const Transform& worldTransformA, 
				Maths::Vector3 aLocalDir, Vector3 expansion = Vector3(0, 0, 0));

			static Vector3 CheckTriangleSimplex(Simplex &s, bool checkAbove = true);
			static bool	CheckTetrahedronSimplex(Simplex &s);
			GJKAlgorithm()	{}
			~GJKAlgorithm() {}
		};
	}
}

