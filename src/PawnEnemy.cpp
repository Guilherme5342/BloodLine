#include "PawnEnemy.hpp"

PawnEnemy::PawnEnemy(GameObject associated, std::string filePath, int health, int damage, EnemyTypePhysics phys
	, float radius, std::weak_ptr<GameObject> player)
  :  EnemyBase(associated,filePath,health,damage,phys), rangeDetection(radius), player(player)
{
}

PawnEnemy::~PawnEnemy()
{
}

void PawnEnemy::Update(float dt)
{
	if (player.expired())
		return;
}

void PawnEnemy::Move()
{
}

void PawnEnemy::Attack()
{
}

void PawnEnemy::SpecialAttack()
{
}
