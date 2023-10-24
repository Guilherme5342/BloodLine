#include "States.hpp"
#include "Collider.hpp"
#include "Game.hpp"

IdleState::IdleState(std::string filePath) 
{
	this->filePath = filePath;

	GameObject* idleObj = new GameObject();
	playerIdle = new Sprite(*idleObj, filePath, 3, 2);
	//playerIdle->Open(filePath);
	//Game::Instance().GetState().AddObject(idleObj);
}

void IdleState::Enter(StateMachine& otherState)
{

}

void IdleState::Exit(StateMachine& otherState)
{
}

void IdleState::Update(StateMachine& state, float dt)
{
	
}

void IdleState::Render(StateMachine& state)
{
	
}

#pragma region AttackState
AttackState::AttackState(int damageAmount, std::string filePath, int range, int timeAmount)
{
	this->damage = damageAmount, this->range = range;
	this->timer = timeAmount;

	GameObject* attackObj = new GameObject();
	attackAnimation = new Sprite(*attackObj, filePath,3,2,.3f);
	//Game::Instance().GetState().AddObject(attackObj);

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
		
		attackTimer.Reset();
		
		stateMachine.AddState(new IdleState(PLAYER_IDLE));
	}
	
	attackTimer.Update(dt);
}
void AttackState::Render(StateMachine& stateMachine)
{
	
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

void DeathState::Render(StateMachine& stateMachine)
{
}

#pragma endregion


