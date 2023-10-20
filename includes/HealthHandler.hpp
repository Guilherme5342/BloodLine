#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

class HealthHandler : public Component {

private:
	int health;

public:
	HealthHandler(GameObject& associated, int health);
	~HealthHandler();

	void Update(float dt);
	void Render();

	inline bool Is(std::string type) {
		return type == "HealthHandler";
	}

	inline void AddHealth(int health) {
		this->health += health;
	}

	inline void RemoveHealth(int health) {
		this->health -= health;
	}


};