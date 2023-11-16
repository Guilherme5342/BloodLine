#include "EnemyBase.hpp"


EnemyBase::EnemyBase(GameObject& associated, std::weak_ptr<GameObject> player,std::string filePath
	, int health, int damage,Action initialAction, EnemyTypePhysics enemyPhys)
	: Component(associated),
	player(player),
	sprite(associated,filePath),
	health(associated,health),
	rb(associated),
	damage(damage)
{
	enemyAction = initialAction;

	associated.AddComponent(&sprite);
	associated.AddComponent(&this->health);
	associated.AddComponent(&rb);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float dt)
{
	switch (enemyAction)
	{
		case IDLE:
			Idle();
			break;
		case MOVE:
			Move();
			break;
		case ATTACK:
			Attack();
			break;
		case MAGIC_SPELL:
			SpecialAttack();
			break;
	}
}

void EnemyBase::Render()
{
}
