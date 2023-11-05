#include "EnemyBase.hpp"

EnemyBase::EnemyBase(GameObject& associated, Sprite& sprite, int health, int damage, EnemyTypePhysics enemyPhys) 
  : Component(associated),
	sprite(sprite),
	health(associated,health),
	rb(associated),
	damage(damage)
{
	switch (enemyPhys)
	{
	case GROUND:
		break;
	case FLY:
		// TODO rb.SetGravity(0)
		break;
	}

}

EnemyBase::EnemyBase(GameObject& associated, std::string filePath, int health, int damage, EnemyTypePhysics enemyPhys)
	: Component(associated),
	sprite(associated,filePath),
	health(associated,health),
	rb(associated),
	damage(damage)
{
}

void EnemyBase::Update(float dt)
{
}

void EnemyBase::Render()
{
}
