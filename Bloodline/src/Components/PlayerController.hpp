#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"

#include "Galapagos/Components/Rigidbody2D.hpp"
#include "Galapagos/Core/InputManager.hpp"

#include "Interfaces/AnimationStates.hpp"
#include "Galapagos/Components/StateMachine.hpp"
#include "Components/Spells/Spell.hpp"

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

	Vec2 moveDir;

	Rigidbody2D &playerBody;

	AnimState *animState;

	std::map<std::string, Spell *> spells;

public:
	PlayerController(GameObject &associated, Sprite &sprite, Rigidbody2D &body, int speed);
	~PlayerController();

	int GetHealth();

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() const override;

	inline virtual bool Is(std::string type) const override
	{
		return type == "PlayerController";
	}

	bool IsDead();

	void CastSpell(std::string spellName);
	void AddSpell(std::string spellName, Spell *spell);

	void NotifyCollision(GameObject &otherObj);
	void NotifyNoCollision(GameObject &otherObj);
};