#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

#include "Rigidbody2D.hpp"
#include "InputSystem.hpp"
#include "Command.hpp"
#include "States.hpp"
#include "StateMachine.hpp"
#include "Spell.hpp"

#include <map>

const int DASH_SPEED_MULTIPLIER = 1000;
const float DASH_COOLDOWN = 2.0f;
const float DASH_DURATION = 0.2f;

class Spell;

class PlayerController : public StateMachine
{

private:
	int speed;

	int health = 100;

	float jumpForce = 100.0f;
	float dashTimer = 0.0f;

	bool jumping = false;
	bool dashing = false;
	bool moving = false;

	float dashElapsedTime;

	bool canJump = false;
	bool canDash = false;

	bool dead = false;

	Vector2 moveDir;

	Rigidbody2D &playerBody;

	AnimState *animState;

	std::map<std::string, Spell *> spells;

public:
	PlayerController(GameObject &associated, Sprite &sprite, Rigidbody2D &body, int speed);
	~PlayerController();

	int GetHealth();

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override
	{
		return type == "PlayerController";
	}

	bool IsDead();

	void CastSpell(std::string spellName);
	void AddSpell(std::string spellName, Spell *spell);

	void NotifyCollision(GameObject &otherObj);
	void NotifyNoCollision(GameObject &otherObj);
};