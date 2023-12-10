#include "PawnEnemy.hpp"
#include "Game.hpp"

#ifdef _WIN32
#define ENEMY_PATH "assets/img/enemies/knight/_Run.png"
#else
#define ENEMY_PATH "../assets/img/enemies/knight/_Run.png"
#endif

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
	hitBox.SetScale(12, 35);
	hitBox.SetOffset({ -1,10 });

	Collider* squareDetectorRight = new Collider(associated, { 25,25 }, { associated.box.x + 50,0 }, true);
	Collider* squareDetectorLeft = new Collider(associated, { 25,25 }, { -associated.box.x - 50,0 }, true);

	Game::Instantiate(squareDetectorLeft, Vector2(25, 25));
}

void PawnEnemy::Render() {

	Vector2 leftPoint = associated.box.GetCenter() - Vector2(102, associated.box.y);
	Vector2 rightPoint = associated.box.GetCenter() + Vector2(102, associated.box.y);

	SDL_Point pointLeft = { static_cast<int>(leftPoint.x), static_cast<int>(leftPoint.y) };
	SDL_Point pointRight = { static_cast<int>(rightPoint.x), static_cast<int>(rightPoint.y) };

	SDL_Point offsetPoints[] = {pointLeft,pointRight};

	SDL_SetRenderDrawColor(Game::GetRenderer(), 255, 255, 8, 255);
	SDL_SetRenderDrawBlendMode(Game::GetRenderer(), SDL_BLENDMODE_BLEND);

	SDL_RenderDrawPoints(Game::GetRenderer(), offsetPoints,2);

}

void PawnEnemy::NotifyCollision(GameObject& otherObj)
{
	Collider* otherColl = (Collider*)otherObj.GetComponent("Collider");
	
	Rect edgeRect = hitBox.box.GetIntersection(otherColl->box);

	if (otherObj.tag == "Ground") {
		
		//cout << edgeRect.x << " " << hitBox.box.x << endl;
				
		sprite.Open(ENEMY_PATH, 10, 1);
		SetActionState(IDLE);
		ChangeMovePoint();
		

	}
}

void PawnEnemy::Idle(float dt)
{
	waitingTimer.Update(dt);
	if (waitingTimer.Get() > 1.5f /*&& isOnFloor*/)
	{
		sprite.Open(ENEMY_PATH, 10, 1);
		ChangeMovePoint();
		SetActionState(MOVE);
		waitingTimer.Reset();
	}
}

void PawnEnemy::Move(float dt)
{
	associated.box += speed.normalized() * dt * 100;
}

void PawnEnemy::Attack(float dt)
{
	Vector2 playerPos = player.lock()->box.GetCenter();
}

void PawnEnemy::SpecialAttack(float dt)
{
}
