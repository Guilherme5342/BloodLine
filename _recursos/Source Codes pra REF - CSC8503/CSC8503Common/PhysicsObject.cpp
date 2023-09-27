#include "PhysicsObject.h"

using namespace NCL;
using namespace CSC8503;

PhysicsObject::PhysicsObject(Transform* parentTransform, const BoundingVolume* parentVolume)
{
	transform	= parentTransform;
	volume		= parentVolume;

	inverseMass = 1.0f;
	elasticity	= 1.0f;
	friction	= 1.0f;
}

PhysicsObject::~PhysicsObject()
{

}

void PhysicsObject::AddForce(const Vector3& force) {

}

void PhysicsObject::AddForceAtPosition(const Vector3& force, const Vector3& position) {

}

void PhysicsObject::AddTorque(const Vector3& torque) {

}

void PhysicsObject::ClearForces() {
	acceleration	= Vector3();
	torque			= Vector3();
}