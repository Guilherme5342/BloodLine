#include "States.hpp"

#include "Collider.hpp"



#pragma region AttackState
AttackState::AttackState(int damageAmount, std::string filePath, int range, int timeAmount)
{
	attackAnimation = nullptr;

	this->damage = damageAmount, this->range = range;
	this->timer = timeAmount;

	attackAnimation->Open(filePath);
}


AttackState::~AttackState()
{
}

void AttackState::Enter(StateMachine& stateMachine)
{
	
}

void AttackState::Exit(StateMachine& stateMachine)
{
}

void AttackState::Update(StateMachine& stateMachine, float dt)
{
	if (attackTimer.Get() > timer) {

	}
	attackTimer.Update(dt);
}
#pragma endregion

#pragma region DeathState

void DeathState::Enter(StateMachine& stateMachine)
{
}

void DeathState::Exit(StateMachine& stateMachine)
{
}

void DeathState::Update(StateMachine& stateMachine, float dt)
{
}

#pragma endregion
