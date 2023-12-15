#pragma once

#include <map>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Components/Rigidbody2D.hpp"
#include "Galapagos/Components/StateMachine.hpp"

#include "Components/Spells/Spell.hpp"
#include "Interfaces/AnimationStates.hpp"

const int DASH_SPEED_MULTIPLIER = 1000;
const float DASH_COOLDOWN = 2.0f;
const float DASH_DURATION = 0.2f;

class Spell;

class PlayerController : public StateMachine
{
public:
	PlayerController(GameObject &associated, AnimatedSprite &sprite, Rigidbody2D &body, int speed);
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

private:
	int m_speed;

	int m_health = 100;

	float m_jumpForce = 100.0f;
	float m_dashTimer = 0.0f;

	bool m_jumping = false;
	bool m_dashing = false;
	bool m_moving = false;

	float m_dashElapsedTime;

	bool m_canJump = false;
	bool m_canDash = false;

	bool m_dead = false;

	Vec2 m_moveDir;

	Rigidbody2D &m_playerBody;

	AnimState *m_animState;

	std::map<std::string, Spell *> m_spells;
};