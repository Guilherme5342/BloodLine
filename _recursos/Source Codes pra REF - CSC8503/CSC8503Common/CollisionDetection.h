#pragma once

#include "../Common/Ray.h"
#include "../Common/Camera.h"

#include "Transform.h"
#include "GameObject.h"

#include "BoundingAABB.h"
#include "BoundingOOBB.h"
#include "BoundingSphere.h"

using NCL::Camera;
using namespace NCL::Maths;
using namespace NCL::CSC8503;
namespace NCL {
	class CollisionDetection
	{
	public:


		static Ray BuildRayFromMouse(const Camera& c);

		static bool RayIntersection(const Ray& r, const Transform& worldTransform, const BoundingVolume& volume, RayCollision<GameObject*> &collisions);
		static bool RayIntersection(const Ray&r, const Transform& worldTransform, const BoundingAABB& volume, RayCollision<GameObject*>& collision);
		static bool RayIntersection(const Ray&r, const Transform& worldTransform, const BoundingOOBB& volume, RayCollision<GameObject*>& collision);
		static bool RayIntersection(const Ray&r, const Transform& worldTransform, const BoundingSphere& volume, RayCollision<GameObject*>& collision);

		static bool RayIntersection(const Ray&r, const Plane&p, RayCollision<float*> &collisions);

		static Vector3 Unproject(const Vector3& screenPos, const Camera& cam);

	protected:

		static Vector3		UnprojectScreenPosition(Vector3 position, float aspect, float fov, const Camera &c);
		static Matrix4		GenerateInverseProjection(float aspect, float fov, float nearPlane, float farPlane);
		static Matrix4		GenerateInverseView(const Camera &c);
	
	private:
		CollisionDetection()	{}
		~CollisionDetection()	{}
	};
}

