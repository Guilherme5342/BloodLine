#include "HealthHandler.hpp"

HealthHandler::HealthHandler(GameObject& associated, int health) : Component(associated), health(health)
{
	
}

HealthHandler::~HealthHandler() {
	associated.RequestDelete();
}
