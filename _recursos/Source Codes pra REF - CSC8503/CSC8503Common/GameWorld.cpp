#include "GameWorld.h"
#include "GameObject.h"
#include "CollisionDetection.h"
#include "../Common/Camera.h"
#include <algorithm>

using namespace NCL;
using namespace NCL::CSC8503;

GameWorld::GameWorld()
{
	mainCamera = new Camera();


}

GameWorld::~GameWorld()
{
}

void GameWorld::Clear() {
	gameObjects.clear();
}

void GameWorld::ClearAndErase() {
	for (auto& i : gameObjects) {
		delete i;
	}
	Clear();
}

void GameWorld::AddGameObject(GameObject* o) {
	gameObjects.emplace_back(o);
}

void GameWorld::RemoveGameObject(GameObject* o) {
	std::remove(gameObjects.begin(), gameObjects.end(), o);
}

void GameWorld::GetObjectIterators(
	std::vector<GameObject*>::const_iterator& first,
	std::vector<GameObject*>::const_iterator& last) const {

	first	= gameObjects.begin();
	last	= gameObjects.end();
}

void GameWorld::UpdateTransforms() {
	for (auto& i : gameObjects) {
		i->GetTransform().UpdateMatrices();
	}
}

void GameWorld::UpdateWorld(float dt, bool updateCam) {
	UpdateTransforms();
	if (updateCam) {
		mainCamera->UpdateCamera(dt);
	}
}

bool GameWorld::Raycast(Ray& r, GameObject** o) const {
	//The simplest raycast just goes through each object and sees if there's a collision
	RayCollision<GameObject*> collision;
	for (auto& i : gameObjects) {
		if (i->GetBoundingVolume()) { //objects might not be collideable etc...
			if (CollisionDetection::RayIntersection(r, i->GetTransform(), *i->GetBoundingVolume(), collision)) {
				*o = i;
				return true;
			}
		}
	}
	return false;
}