#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

#include "Rigidbody2D.hpp"
#include "InputSystem.hpp"
#include "Command.hpp"
#include "States.hpp"
#include "StateMachine.hpp"

const int DASH_SPEED_MULTIPLIER = 1000;
const float DASH_COOLDOWN = 2.0f;
const float DASH_DURATION = 0.2f;

class PlayerController : public StateMachine
{

private:
	int speed;

	float jumpForce = 100.0f;
	float dashTimer = 0.0f;

	bool jumping = false;
	bool dashing = false;
	bool moving = false;

	float dashElapsedTime;

	bool canJump = false;
	bool canDash = false;

	Vector2 moveDir;

	Rigidbody2D &playerBody;

	AnimState *animState;

public:
	PlayerController(GameObject &associated, Sprite &sprite, Rigidbody2D &body, int speed);
	~PlayerController();

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override
	{
		return type == "PlayerController";
	}

	void NotifyCollision(GameObject &otherObj);
};