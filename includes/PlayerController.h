#pragma once

#include "Component.h"
#include "GameObject.h"

#include "InputSystem.h"
#include "Command.h"

class PlayerController : public Component {

private:
	int speed;

public:

	PlayerController(GameObject& associated, int speed);
	~PlayerController();

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override {
		return type == "PlayerController";
	}
};