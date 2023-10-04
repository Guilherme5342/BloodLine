#pragma once

#include "Component.h"
#include "GameObject.h"

#include "Rigidbody2D.h"
#include "InputSystem.h"
#include "Command.h"

class PlayerController : public Component {

private:
	int speed;

	float jumpForce = 1000.0f;

	bool jumping;

	Vector2 moveDir;

	Rigidbody2D& playerBody;

public:

	PlayerController(GameObject& associated,Rigidbody2D& body,int speed);
	~PlayerController();

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override {
		return type == "PlayerController";
	}
};