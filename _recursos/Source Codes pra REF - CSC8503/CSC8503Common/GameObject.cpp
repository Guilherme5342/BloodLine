#include "GameObject.h"

using namespace NCL::CSC8503;

GameObject::GameObject(string objectName)
{
	name			= objectName;
	isActive		= true;
	boundingVolume	= nullptr;
	physicsObject	= nullptr;
	renderObject	= nullptr;
}

GameObject::~GameObject()
{
}
