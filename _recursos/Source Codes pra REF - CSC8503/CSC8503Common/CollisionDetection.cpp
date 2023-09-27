#include "CollisionDetection.h"
#include "BoundingVolume.h"
#include "BoundingAABB.h"
#include "BoundingOOBB.h"
#include "BoundingSphere.h"
#include "../Common/Vector2.h"
#include "../Common/Window.h"
#include "../Common/Maths.h"

using namespace NCL;

bool CollisionDetection::RayIntersection(const Ray&r, const Plane&p, RayCollision<float*> &collisions) {
	float ln = Vector3::Dot(p.GetNormal(), r.GetDirection());

	if (ln == 0.0f) {
		return false; //direction vectors are perpendicular!
	}
	
	Vector3 planePoint = p.GetPointOnPlane();

	Vector3 pointDir = planePoint - r.GetPosition();

	float d = Vector3::Dot(pointDir, p.GetNormal()) / ln;

	collisions.collidedAt = r.GetPosition() + (r.GetDirection() * d);

	return true;
}

bool CollisionDetection::RayIntersection(const Ray& r, const Transform& worldTransform, const BoundingVolume& volume, RayCollision<GameObject*> &collision) {
	bool hasCollided = false;
	switch (volume.type) {
		case BoundingType::AABB:	hasCollided = RayIntersection(r, worldTransform, (const BoundingAABB&)volume	, collision); break;
		case BoundingType::OOBB:	hasCollided = RayIntersection(r, worldTransform, (const BoundingOOBB&)volume	, collision); break;
		case BoundingType::Sphere:	hasCollided = RayIntersection(r, worldTransform, (const BoundingSphere&)volume	, collision); break;
	}

	return hasCollided;
}
//https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
bool CollisionDetection::RayIntersection(const Ray&r, const Transform& worldTransform, const BoundingAABB& volume, RayCollision<GameObject*>& collision) {
	Vector3	boxPos	= worldTransform.GetWorldPosition();
	Vector3 boxSize = volume.GetHalfDimensions();

	Vector3 boxMin = boxPos - boxSize;
	Vector3 boxMax = boxPos + boxSize;

	Vector3 rayPos	= r.GetPosition();
	Vector3 rayDir	= r.GetDirection();

	Vector3 tVals;

	for (int i = 0; i < 3; ++i) {
		if (rayDir[i] > 0) {
			//if we're going forward along an axis, test against the 'min' side of that box
			tVals[i] = (boxMin[i] - rayPos[i]) / rayDir[i];
		}
		else {
			//but if we're going backward along an axis, test against the max side instead
			tVals[i] = (boxMax[i] - rayPos[i]) / rayDir[i];
		}
	}
	//The tVal with the largest value is the plane we actually intersected with
	//we can then travel along the ray by T to get the intersection point
	Vector3 intersection = rayPos + (rayDir * tVals.GetMaxElement());

	for (int i = 0; i < 3; ++i) {
		if (intersection[i] < boxMin[i] || intersection[i] > boxMax[i]) {
			return false;
		}
	}

	return true;
}

bool CollisionDetection::RayIntersection(const Ray&r, const Transform& worldTransform, const BoundingOOBB& volume, RayCollision<GameObject*>& collision) {

	return false;
}

bool CollisionDetection::RayIntersection(const Ray&r, const Transform& worldTransform, const BoundingSphere& volume, RayCollision<GameObject*>& collision) {
	Vector3	spherePos		= worldTransform.GetWorldPosition();
	float	sphereRadius	= volume.GetRadius();

	//Get the direction vector between the ray origin and the sphere origin
	Vector3 sphereDirection = (spherePos - r.GetPosition());

	//Then project the sphere's origin onto our ray direction vector

	float sphereProjectBy = Vector3::Dot(sphereDirection, r.GetDirection());

	Vector3 puv = r.GetDirection() * sphereProjectBy;

	//Now we know the projection point onto the direction vector
	//If it's further away than the radius of the sphere, it logically cannot be intersecting!
	Vector3 point	= r.GetPosition() + puv; //This is the point along the ray dir that the sphere direction projects on to.

	float sphereDist = (point - spherePos).Length();

	if (sphereDist > sphereRadius) {
		return false;
	}
	//for now we'll just return true;
	return true;
}

Matrix4 GenerateInverseView(const Camera &c) {
	float pitch = c.GetPitch();
	float yaw = c.GetYaw();
	Vector3 position = c.GetPosition();

	Matrix4 iview =
		Matrix4::Translation(position) *
		Matrix4::Rotation(-yaw, Vector3(0, -1, 0)) *
		Matrix4::Rotation(-pitch, Vector3(-1, 0, 0));

	return iview;
}

Matrix4 GenerateInverseProjection(float aspect, float nearPlane, float farPlane, float fov) {
	float negDepth = nearPlane - farPlane;

	float invNegDepth = negDepth / (2 * (farPlane * nearPlane));

	Matrix4 m;

	float h = 1.0f / tan(fov*PI_OVER_360);

	m.values[0] = aspect / h;
	m.values[5] = tan(fov*PI_OVER_360);
	m.values[10] = 0.0f;

	m.values[11] = invNegDepth;//// +PI_OVER_360;
	m.values[14] = -1.0f;
	m.values[15] = (0.5f / nearPlane) + (0.5f / farPlane);

	//Matrix4 temp = projection.Inverse();
	//return temp;
	return m;
}

Vector3 CollisionDetection::Unproject(const Vector3& screenPos, const Camera& cam) {
	Vector2 screenSize = Window::GetWindow()->GetScreenSize();

	float aspect	= screenSize.x / screenSize.y;
	float fov		= cam.GetFieldOfVision();
	float nearPlane = cam.GetNearPlane();
	float farPlane  = cam.GetFarPlane();

	//Create our inverted matrix! Note how that to get a correct inverse matrix,
	//the order of matrices used to form it are inverted, too.
	Matrix4 invVP = GenerateInverseView(cam) * GenerateInverseProjection(aspect, fov, nearPlane, farPlane);

	Matrix4 test1 = GenerateInverseView(cam);
	Matrix4 test2 = cam.BuildViewMatrix().Inverse();

	Matrix4 proj = cam.BuildProjectionMatrix(aspect);
	Matrix4 test4 = cam.BuildProjectionMatrix(aspect).Inverse();
	Matrix4 test3 = GenerateInverseProjection(aspect, fov, nearPlane, farPlane);


	//Our mouse position x and y values are in 0 to screen dimensions range,
	//so we need to turn them into the -1 to 1 axis range of clip space.
	//We can do that by dividing the mouse values by the width and height of the
	//screen (giving us a range of 0.0 to 1.0), multiplying by 2 (0.0 to 2.0)
	//and then subtracting 1 (-1.0 to 1.0).
	Vector4 clipSpace = Vector4(
		(screenPos.x / (float)screenSize.x) * 2.0f - 1.0f,
		(screenPos.y / (float)screenSize.y) * 2.0f - 1.0f,
		(screenPos.z),
		1.0f
	);

	//Then, we multiply our clipspace coordinate by our inverted matrix
	Vector4 transformed = invVP * clipSpace;

	//our transformed w coordinate is now the 'inverse' perspective divide, so
	//we can reconstruct the final world space by dividing x,y,and z by w.
	return Vector3(transformed.x / transformed.w, transformed.y / transformed.w, transformed.z / transformed.w);

}


Ray CollisionDetection::BuildRayFromMouse(const Camera& cam) {
	Vector2 screenMouse = Window::GetMouse()->GetAbsolutePosition();
	Vector2 screenSize = Window::GetWindow()->GetScreenSize();

	//We remove the y axis mouse position from height as OpenGL is 'upside down',
	//and thinks the bottom left is the origin, instead of the top left!
	Vector3 nearPos = Vector3(screenMouse.x,
		screenSize.y - screenMouse.y,
		-0.99999f
	);

	//We also don't use exactly 1.0 (the normalised 'end' of the far plane) as this
	//causes the unproject function to go a bit weird. 
	Vector3 farPos = Vector3(screenMouse.x,
		screenSize.y - screenMouse.y,
		0.99999f
	);

	Vector3 a = Unproject(nearPos, cam);
	Vector3 b = Unproject(farPos, cam);
	Vector3 c = b - a;

	c.Normalise();

	std::cout << "Ray Direction:" << c << std::endl;

	return Ray(cam.GetPosition(), c);
}



Matrix4 CollisionDetection::GenerateInverseProjection(float aspect, float fov, float nearPlane, float farPlane) {
	Matrix4 m;

	float t = tan(fov*PI_OVER_360);

	float neg_depth = nearPlane - farPlane;

	const float h = 1.0f / t;

	m.values[0] = aspect / h;
	m.values[5] = tan(fov*PI_OVER_360);


	m.values[10] = 1.0f + ((farPlane + nearPlane) / neg_depth);

	m.values[11] = -0.5f;	//should be ok
	m.values[14] = -1.0f + (1.0f / (2.0f*(nearPlane*farPlane) / neg_depth));
	m.values[15] = 0.5f;	//should be ok

	return m;
}

/*
And here's how we generate an inverse view matrix. It's pretty much
an exact inversion of the BuildViewMatrix function of the Camera class!
*/
Matrix4 CollisionDetection::GenerateInverseView(const Camera &c) {
	float pitch = c.GetPitch();
	float yaw	= c.GetYaw();
	Vector3 position = c.GetPosition();

	Matrix4 iview =
		Matrix4::Translation(position) *
		Matrix4::Rotation(-yaw, Vector3(0, -1, 0)) *
		Matrix4::Rotation(-pitch, Vector3(-1, 0, 0));

	return iview;
}


/*
If you've read through the Deferred Rendering tutorial you should have a pretty
good idea what this function does. It takes a 2D position, such as the mouse
position, and 'unprojects' it, to generate a 3D world space position for it.

Just as we turn a world space position into a clip space position by multiplying
it by the model, view, and projection matrices, we can turn a clip space
position back to a 3D position by multiply it by the INVERSE of the
view projection matrix (the model matrix has already been assumed to have
'transformed' the 2D point). As has been mentioned a few times, inverting a
matrix is not a nice operation, either to understand or code. But! We can cheat
the inversion process again, just like we do when we create a view matrix using
the camera.

So, to form the inverted matrix, we need the aspect and fov used to create the
projection matrix of our scene, and the camera used to form the view matrix.

*/
Vector3	CollisionDetection::UnprojectScreenPosition(Vector3 position, float aspect, float fov, const Camera &c) {
	//Create our inverted matrix! Note how that to get a correct inverse matrix,
	//the order of matrices used to form it are inverted, too.
	Matrix4 invVP = GenerateInverseView(c) * GenerateInverseProjection(aspect, fov, c.GetNearPlane(), c.GetFarPlane());

	Vector2 screenSize = Window::GetWindow()->GetScreenSize();

	//Our mouse position x and y values are in 0 to screen dimensions range,
	//so we need to turn them into the -1 to 1 axis range of clip space.
	//We can do that by dividing the mouse values by the width and height of the
	//screen (giving us a range of 0.0 to 1.0), multiplying by 2 (0.0 to 2.0)
	//and then subtracting 1 (-1.0 to 1.0).
	Vector4 clipSpace = Vector4(
		(position.x / (float)screenSize.x) * 2.0f - 1.0f,
		(position.y / (float)screenSize.y) * 2.0f - 1.0f,
		(position.z) - 1.0f,
		1.0f
	);

	//Then, we multiply our clipspace coordinate by our inverted matrix
	Vector4 transformed = invVP * clipSpace;

	//our transformed w coordinate is now the 'inverse' perspective divide, so
	//we can reconstruct the final world space by dividing x,y,and z by w.
	return Vector3(transformed.x / transformed.w, transformed.y / transformed.w, transformed.z / transformed.w);
}