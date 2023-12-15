#pragma once

#include "GameDefines/GlobalDefinitions.hpp"
#include "Galapagos/Components/StateMachine.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Utils/Timer.hpp"
#include "Components/PlayerController.hpp"

class IdleState : public AnimState
{
public:
	IdleState(Sprite &sprite);

	// Herdado por meio de IState
	virtual void OnEnter(StateMachine &otherState) override;
	virtual void OnExit(StateMachine &otherState) override;

	virtual void Update(StateMachine &state, float dt) override;
	virtual void Render(const StateMachine &state) override;
};

class MovingState : public AnimState
{
public:
	MovingState(Sprite &sprite);
	~MovingState();

	virtual void OnEnter(StateMachine &otherState) override;
	virtual void OnExit(StateMachine &otherState) override;

	virtual void Update(StateMachine &state, float dt) override;
	virtual void Render(const StateMachine &state) override;

private:
	Timer m_moveTimer;
};
/// <summary>
/// Estado Generico de Ataque
/// </summary>
class AttackState : public AnimState
{
public:
	AttackState(Sprite &sprite, int damageAmount, int range, int timer = 1);
	~AttackState();

	void OnEnter(StateMachine &stateMachine);
	void OnExit(StateMachine &stateMachine);

	void Update(StateMachine &stateMachine, float dt);
	void Render(const StateMachine &stateMachine);

private:
	int m_damage;

	int m_range, m_timer;

	Timer m_attackTimer;
};

/// <summary>
/// Estado gen�rico de Morte
/// </summary>
class DeathState : public AnimState
{
public:
	DeathState(Sprite &sprite);
	void OnEnter(StateMachine &stateMachine);
	void OnExit(StateMachine &stateMachine);

	void Update(StateMachine &stateMachine, float dt);
	void Render(const StateMachine &stateMachine);
};

class DashState : public AnimState
{
public:
	DashState(Sprite &sprite);
	virtual ~DashState();

	void Update(StateMachine &state, float dt) override;
	void Render(const StateMachine &state) override;

private:
	Sprite &m_sprite;
	float m_dashTime;
	static const float DASH_DURATION; // Duration of the dash animation/state
};