#pragma once

#include "GlobalDefinitions.hpp"
#include "StateMachine.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"

class IdleState : public AnimState {


public:
	IdleState(Sprite& sprite);

	// Herdado por meio de IState
	virtual void OnEnter(StateMachine& otherState) override;
	virtual void OnExit(StateMachine& otherState) override;

	virtual void Update(StateMachine& state, float dt) override;
	virtual void Render(StateMachine& state) override;

};

class MovingState : public AnimState {

private:

	Timer moveTimer;

public:
	MovingState(Sprite& sprite);
	~MovingState();

	virtual void OnEnter(StateMachine& otherState) override;
	virtual void OnExit(StateMachine& otherState) override;

	virtual void Update(StateMachine& state, float dt) override;
	virtual void Render(StateMachine& state) override;


};
/// <summary>
/// Estado Generico de Ataque
/// </summary>
class AttackState : public AnimState {

private:
	int damage;

	int range, timer;

	Timer attackTimer;

public:
	AttackState(Sprite& sprite, int damageAmount, int range, int timer = 1);
	~AttackState();

	void OnEnter(StateMachine& stateMachine);
	void OnExit(StateMachine& stateMachine);

	void Update(StateMachine& stateMachine, float dt);
	void Render(StateMachine& stateMachine);
};




/// <summary>
/// Estado genérico de Morte
/// </summary>
class DeathState : public AnimState {

public:
	DeathState(Sprite& sprite);
	void OnEnter(StateMachine& stateMachine);
	void OnExit(StateMachine& stateMachine);

	void Update(StateMachine& stateMachine, float dt);
	void Render(StateMachine& stateMachine);
};