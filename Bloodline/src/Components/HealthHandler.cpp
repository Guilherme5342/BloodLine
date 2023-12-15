#include "HealthHandler.hpp"
#include "Galapagos/Core/GameObject.hpp"

HealthHandler::HealthHandler(GameObject& associated, int health) : Component(associated), health(health)
{
	this->health = health;
}

HealthHandler::~HealthHandler() {
	
}

int HealthHandler::GetHealth() {
	return health;
}

void HealthHandler::Update(float dt)
{
	if (health <= 0) {
		m_associated.RequestDelete();
	}
}

void HealthHandler::Render() const
{
}
