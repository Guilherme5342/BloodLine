#pragma once

#include "StateMachine.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"

/// <summary>
/// Estado Generico de Ataque
/// </summary>
class AttackState : public IState {

private:
	int damage;
	Sprite* attackAnimation;

	int range, timer;

	Timer attackTimer;

public:
	AttackState(int damageAmount, std::string filePath, int range, int timer = 1);
	~AttackState();

	void Enter(StateMachine& stateMachine);
	void Exit(StateMachine& stateMachine);

	void Update(StateMachine& stateMachine, float dt);
};


/// <summary>
/// Estado genérico de Morte
/// </summary>
class DeathState : public IState {

public:
	void Enter(StateMachine& stateMachine);
	void Exit(StateMachine& stateMachine);

	void Update(StateMachine& stateMachine, float dt);
};