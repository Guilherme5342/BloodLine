#pragma once
#include "Simplex.h"
#include "OBBVolume.h"
#include "CollisionDetection.h"
#include <list>
namespace NCL {		
		namespace Maths {
			class Simplex;
			class Vector3;
		}
	namespace CSC8503 {
		class Transform;
		class EPAAlgorithm
		{		
		protected:
			struct EPATriangle {
				Simplex::SupportPoint a;
				Simplex::SupportPoint b;
				Simplex::SupportPoint c;
				Vector3 normal;

				EPATriangle(Simplex::SupportPoint &a, Simplex::SupportPoint &b, Simplex::SupportPoint&c) {
					this->a = a;
					this->b = b;
					this->c = c;

					Vector3 ba = b.pos = a.pos;
					Vector3 ca = c.pos = a.pos;

					this->normal = Vector3::Cross(ba, ca);
					this->normal.Normalise();
				}
			};

			struct EPAEdge {
				Simplex::SupportPoint a;
				Simplex::SupportPoint b;

				EPAEdge(Simplex::SupportPoint& a, Simplex::SupportPoint &b) {
					this->a = a;
					this->b = b;
				}

			};
		public:
			EPAAlgorithm();
			~EPAAlgorithm();

			void EPASimplexCalculator(Simplex& simplex, const OBBVolume& volumeA, const Transform& worldTransformA,
				const NCL::OBBVolume& volumeB, const Transform& worldTransformB, CollisionDetection::CollisionInfo& collisionInfo);

		protected:
			void GetBestTriangle(std::list<EPATriangle>& list, EPATriangle& outTri, float& outDist);
		};
	}
}

