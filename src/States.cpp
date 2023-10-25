#include "States.hpp"
#include "Collider.hpp"
#include "Game.hpp"

IdleState::IdleState() 
{

}

void IdleState::Enter(StateMachine& otherState)
{
	cout << "Entrando no Estado de Idle" << endl;
}

void IdleState::Exit(StateMachine& otherState)
{
	cout << "Saindo do Estado de Idle" << endl;
}

void IdleState::Update(StateMachine& state, float dt)
{
	
}

void IdleState::Render(StateMachine& state)
{

}

MovingState::MovingState(Vector2 moveDir, float speed) : moveDir(moveDir), speed(speed)
{

}

MovingState::~MovingState()
{
}

void MovingState::Enter(StateMachine& otherState)
{

}

void MovingState::Exit(StateMachine& otherState)
{
	moveDir = { 0,0 };
}

void MovingState::Update(StateMachine& state, float dt)
{
	moveDir.x += speed * dt;

	moveTimer.Update(dt);
}

void MovingState::Render(StateMachine& state)
{
}


#pragma region AttackState
AttackState::AttackState(int damageAmount, std::string filePath, int range, int timeAmount)
{
	this->damage = damageAmount, this->range = range;
	this->timer = timeAmount;
}


AttackState::~AttackState()
{
}

void AttackState::Enter(StateMachine& stateMachine)
{
	cout << "Entrando no Estado de Ataque" << endl;
}

void AttackState::Exit(StateMachine& stateMachine)
{
	cout << "Saindo no Estado de Ataque" << endl;
}

void AttackState::Update(StateMachine& stateMachine, float dt)
{
	if (attackTimer.Get() > timer) {
		
		attackTimer.Reset();
		
		stateMachine.SetState(new IdleState(PLAYER_IDLE));
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

