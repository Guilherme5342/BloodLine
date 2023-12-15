#include "HealthHandler.hpp"
#include "Galapagos/Core/GameObject.hpp"

HealthHandler::HealthHandler(GameObject &associated, int health) : Component(associated), m_health(health)
{
	this->m_health = health;
}

HealthHandler::~HealthHandler()
{
}

void HealthHandler::Update(float dt)
{
	if (m_health <= 0)
	{
		m_associated.RequestDelete();
	}
}

void HealthHandler::Render() const
{
}
