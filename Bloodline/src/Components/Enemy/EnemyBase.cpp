#include "EnemyBase.hpp"


EnemyBase::EnemyBase(GameObject& associated, std::weak_ptr<GameObject> player
	, int health, int damage,Action initialAction, EnemyTypePhysics enemyPhys)
	: Component(associated),
	m_player(player),
	m_damage(damage)
{
	m_enemyAction = initialAction;

	m_sprite = new Sprite(associated, PAWN_ENEMY_IDLE);

	associated.AddComponent(m_sprite);

	m_health = new HealthHandler(associated, health);
	associated.AddComponent(m_health);

	m_rb = new Rigidbody2D(associated);
	associated.AddComponent(m_rb);

	m_hitBox = new Collider(associated);
	associated.AddComponent(m_hitBox);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float dt)
{
	if(m_health->GetHealth() <= 0 && !m_associated.IsDead())
	{
		m_associated.RequestDelete();
		return;
	}

	switch (m_enemyAction)
	{
		case Action::IDLE:
			Idle(dt);
			break;
		case Action::MOVE:
			Move(dt);
			break;
		case Action::ATTACK:
			Attack(dt);
			break;
		case Action::MAGIC_SPELL:
			SpecialAttack(dt);
			break;
	}
}

void EnemyBase::Render()
{
}

void EnemyBase::NotifyCollision(GameObject& other)
{
	m_isOnFloor = m_associated.layer == other.layer;
}
