#include "States.hpp"
#include "Collider.hpp"
#include "Game.hpp"

IdleState::IdleState(Sprite &sprite) : AnimState(sprite)
{
}

void IdleState::OnEnter(StateMachine &otherState)
{
	cout << "Entrando no Estado de Idle" << endl;
	Play(PLAYER_IDLE, 10, 1);
}

void IdleState::OnExit(StateMachine &otherState)
{
	//cout << "Saindo do Estado de Idle" << endl;
}

void IdleState::Update(StateMachine &state, float dt)
{
}

void IdleState::Render(StateMachine &state)
{
}

MovingState::MovingState(Sprite &sprite) : AnimState(sprite)
{
}

MovingState::~MovingState()
{
}

void MovingState::OnEnter(StateMachine &otherState)
{
	Play(PLAYER_RUNNING, 8, 1);
}

void MovingState::OnExit(StateMachine &otherState)
{
}

void MovingState::Update(StateMachine &state, float dt)
{
	moveTimer.Update(dt);
}

void MovingState::Render(StateMachine &state)
{
}

#pragma region AttackState
AttackState::AttackState(Sprite &sprite, int damageAmount, int range, int timeAmount)
	: AnimState(sprite)
{
	this->damage = damageAmount, this->range = range;
	this->timer = timeAmount;
}

AttackState::~AttackState()
{
}

void AttackState::OnEnter(StateMachine &stateMachine)
{
	//cout << "Entrando no Estado de Ataque" << endl;
	Play(PLAYER_ATTACK, 3, 2);
}

void AttackState::OnExit(StateMachine &stateMachine)
{
	//cout << "Saindo no Estado de Ataque" << endl;
}

void AttackState::Update(StateMachine &stateMachine, float dt)
{
	if (attackTimer.Get() > timer)
	{

		attackTimer.Reset();
		stateMachine.SetState(new IdleState(spriteAnim));
	}

	attackTimer.Update(dt);
}
void AttackState::Render(StateMachine &stateMachine)
{
}
#pragma endregion

#pragma region DeathState

DeathState::DeathState(Sprite &sprite) : AnimState(sprite)
{
}

void DeathState::OnEnter(StateMachine &stateMachine)
{
}

void DeathState::OnExit(StateMachine &stateMachine)
{
}

void DeathState::Update(StateMachine &stateMachine, float dt)
{
}

void DeathState::Render(StateMachine &stateMachine)
{
}

#pragma endregion

#pragma region DashState

const float DashState::DASH_DURATION = 0.2f; // Initialize the constant

DashState::DashState(Sprite &sprite)
	: sprite(sprite), dashTime(0.0f), AnimState(sprite)
{
	// Constructor body, if needed
}

DashState::~DashState()
{
	// Destructor body, if needed
}

void DashState::Update(StateMachine &state, float dt)
{
	auto *player = dynamic_cast<PlayerController *>(&state);
	if (player)
	{
		dashTime += dt;
		if (dashTime >= DASH_DURATION)
		{
			player->SetState(new IdleState(sprite));
		}
	}
}

void DashState::Render(StateMachine &state)
{
	// Render the sprite with the dash animation frame
	sprite.Render();
}

#pragma endregion
