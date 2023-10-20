#include "HealthHandler.hpp"
#include "GameObject.hpp"
#include "States.hpp"

HealthHandler::HealthHandler(GameObject& associated, int health) : Component(associated), health(health)
{
	this->health = health;
}

HealthHandler::~HealthHandler() {
	
}

void HealthHandler::Update(float dt)
{
	if (health <= 0) {
		associated.RequestDelete();
	}
}

void HealthHandler::Render()
{
}
