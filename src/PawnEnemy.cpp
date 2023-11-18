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

void PawnEnemy::Start()
{
	hitBox.SetOffset(associated.box.GetCenter());
}

void PawnEnemy::Render() {

	Vector2 leftPoint = associated.box.GetCenter() - Vector2(102, associated.box.y);
	Vector2 rightPoint = associated.box.GetCenter() + Vector2(102, associated.box.y);

	SDL_Point pointLeft = { leftPoint.x,leftPoint.y };
	SDL_Point pointRight = { rightPoint.x,rightPoint.y };

	SDL_Point offsetPoints[] = {pointLeft,pointRight};

	SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 255, 255, 8, 255);
	SDL_SetRenderDrawBlendMode(Game::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);

	SDL_RenderDrawPoints(Game::Instance().GetRenderer(), offsetPoints,2);

}

void PawnEnemy::Idle(float dt)
{
	waitingTimer.Update(dt);


	if (waitingTimer.Get() > 2.5f && isOnFloor) 
	{
		
		ChangeMovePoint();

		sprite.Open("assets/img/enemies/knight/_Run.png", 10, 1);
		SetActionState(MOVE);
		
		waitingTimer.Reset();
	}
}

void PawnEnemy::Move(float dt)
{
	
	if (distanceBetweenPoint <= 1) {
		sprite.Open("assets/img/enemies/knight/_Idle.png", 10, 1);
		SetActionState(IDLE);
		invertMove = !invertMove;
	}
	else {

		float angle = Vector2::Angle(associated.box.GetCenter(), destination);
		speed = Vector2::DirectionFrom(angle);

		associated.box += speed.normalized() * dt * 100;
	}


}

void PawnEnemy::Attack(float dt)
{
	Vector2 playerPos = player.lock()->box.GetCenter();
}

void PawnEnemy::SpecialAttack(float dt)
{
}
