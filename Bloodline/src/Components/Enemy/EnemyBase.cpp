#include "EnemyBase.hpp"


EnemyBase::EnemyBase(GameObject& associated, std::weak_ptr<GameObject> player, Sprite& sprite
	, int health, int damage,Action initialAction, EnemyTypePhysics enemyPhys)
	: Component(associated),
	m_player(player),
	m_sprite(sprite),
	m_health(associated,health),
	m_rb(associated),
	m_damage(damage),
	m_hitBox(associated)
{
	m_enemyAction = initialAction;

	Vec2 spriteScale = Vec2(sprite.GetWidth(), sprite.GetHeight());

	associated.m_box.SetSize(spriteScale);

	associated.AddComponent(&sprite);
	associated.AddComponent(&this->m_health);
	associated.AddComponent(&m_rb);
	associated.AddComponent(&m_hitBox);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float dt)
{
	if(m_health.GetHealth() <= 0 && !m_associated.IsDead())
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
