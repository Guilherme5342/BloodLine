#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

#include "Rigidbody2D.hpp"
#include "InputSystem.hpp"
#include "Command.hpp"

class PlayerController : public Component
{

private:
	int speed;

	float jumpForce = 100.0f;

	bool jumping, canJump;

	Vector2 moveDir;

	Rigidbody2D &playerBody;

public:
	PlayerController(GameObject &associated, Rigidbody2D &body, int speed);
	~PlayerController();

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override
	{
		return type == "PlayerController";
	}

	void NotifyCollision(GameObject& otherObj);
};