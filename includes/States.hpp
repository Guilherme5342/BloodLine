#pragma once

#include "GlobalDefinitions.hpp"
#include "StateMachine.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"

class IdleState : public IState {

private:
	std::string filePath;
	Sprite* playerIdle;

public:
	IdleState(std::string filePath);


	// Herdado por meio de IState
	virtual void Enter(StateMachine& otherState) override;

	virtual void Exit(StateMachine& otherState) override;

	virtual void Update(StateMachine& state, float dt) override;

	virtual void Render(StateMachine& state) override;

};
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
	void Render(StateMachine& stateMachine);
};


/// <summary>
/// Estado genérico de Morte
/// </summary>
class DeathState : public IState {

public:
	void Enter(StateMachine& stateMachine);
	void Exit(StateMachine& stateMachine);

	void Update(StateMachine& stateMachine, float dt);
	void Render(StateMachine& stateMachine);
};