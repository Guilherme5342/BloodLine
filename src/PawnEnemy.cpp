#include "PawnEnemy.hpp"
#include "Game.hpp"

PawnEnemy::PawnEnemy(GameObject& associated, std::weak_ptr<GameObject> player, Sprite& filePath, int health,
	int damage, Action enemyAction, EnemyTypePhysics phys, float radius)
  :  EnemyBase(associated, player,filePath,health,damage, enemyAction,phys), rangeDetection(radius)
{
}

PawnEnemy::~PawnEnemy()
{
}

void PawnEnemy::Idle(float dt)
{
	waitingTimer.Update(Game::Instance().GetDeltaTime());
	if (waitingTimer.Get() > 2) 
	{
		SetActionState(MOVE);
		waitingTimer.Reset();
	}
}

void PawnEnemy::Move(float dt)
{
	Vector2 leftPoint = associated.box.GetCenter() - Vector2(20, 20);
	Vector2 rightPoint = associated.box.GetCenter() + Vector2(20,20);
	
	Vector2 destination = invertMove ? leftPoint : rightPoint;
	float distance = Distance(associated.box.GetCenter(), destination);

	if (distance >= 1) {
		SetActionState(IDLE);
	}

}

void PawnEnemy::Attack(float dt)
{
	Vector2 playerPos = player.lock()->box.GetCenter();
}

void PawnEnemy::SpecialAttack(float dt)
{
}
