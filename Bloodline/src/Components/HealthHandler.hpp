#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"

class HealthHandler : public Component
{
public:
	HealthHandler(GameObject &associated, int health);
	~HealthHandler();

	void Update(float dt);
	void Render() const;

	inline bool Is(std::string type) const { return type == "HealthHandler"; }

	inline int GetHealth() { return m_health; }

	inline void AddHealth(int health) { this->m_health += health; }

	inline void RemoveHealth(int health) { this->m_health -= health; }

private:
	int m_health;
};