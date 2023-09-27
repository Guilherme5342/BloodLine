#include "GameObject.h"
#include "CollisionDetection.h"

using namespace NCL::CSC8503;

GameObject::GameObject(string objectName)	{
	name			= objectName;
	isActive		= true;
	boundingVolume	= nullptr;
	physicsObject	= nullptr;
	renderObject	= nullptr;
	networkObject	= nullptr;
}

GameObject::~GameObject()	{
	delete boundingVolume;
	delete physicsObject;
	delete renderObject;
	delete networkObject;
}

bool GameObject::InsideAABB(const Vector3& boxPos, const Vector3& halfSize) {
	if (!boundingVolume) {
		return false;
	}
	return CollisionDetection::AABBTest(transform, *boundingVolume, boxPos, halfSize);
}