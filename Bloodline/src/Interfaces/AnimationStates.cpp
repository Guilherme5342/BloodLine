#include "AnimationStates.hpp"
#include "Galapagos/Components/Collider.hpp"
#include "Galapagos/Core/Game.hpp"

IdleState::IdleState(AnimatedSprite&sprite) : AnimState(sprite)
{
}

void IdleState::OnEnter(StateMachine &otherState)
{
	// cout << "Entrando no Estado de Idle" << endl;
	Play(PLAYER_IDLE, 10, 1);
}

void IdleState::OnExit(StateMachine &otherState)
{
	//cout << "Saindo do Estado de Idle" << endl;
}

void IdleState::Update(StateMachine &state, float dt)
{
}

void IdleState::Render(const StateMachine &state)
{
}

MovingState::MovingState(AnimatedSprite&sprite) : AnimState(sprite)
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
	m_moveTimer.Update(dt);
}

void MovingState::Render(const StateMachine &state)
{
}

#pragma region AttackState
AttackState::AttackState(AnimatedSprite&sprite, int damageAmount, int range, int timeAmount)
	: AnimState(sprite)
{
	this->m_damage = damageAmount, this->m_range = range;
	this->m_timer = timeAmount;
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
	if (m_attackTimer.Get() > m_timer)
	{

		m_attackTimer.Restart();
		stateMachine.SetState(new IdleState(spriteAnim));
	}

	m_attackTimer.Update(dt);
}
void AttackState::Render(const StateMachine &stateMachine)
{
}
#pragma endregion

#pragma region DeathState

DeathState::DeathState(AnimatedSprite&sprite) : AnimState(sprite)
{
}

void DeathState::OnEnter(StateMachine &stateMachine)
{
	std::cout << "Entrando no Estado de Idle" << std::endl;
}

void DeathState::OnExit(StateMachine &stateMachine)
{
}

void DeathState::Update(StateMachine &stateMachine, float dt)
{
}

void DeathState::Render(const StateMachine &stateMachine)
{
}

#pragma endregion

#pragma region DashState

const float DashState::DASH_DURATION = 0.2f; // Initialize the constant

DashState::DashState(AnimatedSprite&sprite)
	: m_sprite(sprite), m_dashTime(0.0f), AnimState(sprite)
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
		m_dashTime += dt;
		if (m_dashTime >= DASH_DURATION)
		{
			player->SetState(new IdleState(m_sprite));
		}
	}
}

void DashState::Render(const StateMachine &state)
{
	// Render the sprite with the dash animation frame
	m_sprite.Render();
}

#pragma endregion
