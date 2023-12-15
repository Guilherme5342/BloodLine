#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"

class HealthHandler : public Component {

private:
	int health;

public:
	HealthHandler(GameObject& associated, int health);
	~HealthHandler();

	int GetHealth();

	void Update(float dt);
	void Render() const;

	inline bool Is(std::string type) const {
		return type == "HealthHandler";
	}

	inline void AddHealth(int health) {
		this->health += health;
	}

	inline void RemoveHealth(int health) {
		this->health -= health;
	}


};