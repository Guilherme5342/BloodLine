#include "PawnEnemy.hpp"
#include "Galapagos/Core/Game.hpp"

PawnEnemy::PawnEnemy(GameObject& m_associated, std::weak_ptr<GameObject> player, Sprite& filePath, int health,
	int damage, Action enemyAction, EnemyTypePhysics phys, float radius)
  :  EnemyBase(m_associated, player,filePath,health,damage, enemyAction,phys), rangeDetection(radius)
{
	
	
}

PawnEnemy::~PawnEnemy()
{

}

void PawnEnemy::Start()
{
	hitBox.SetScale(Vec2(12, 35));
	hitBox.SetOffset({ -1,10 });

	Collider* squareDetectorRight = new Collider(m_associated, { 25,25 }, { m_associated.m_box.x + 50,0 });
	Collider* squareDetectorLeft = new Collider(m_associated, { 25,25 }, { -m_associated.m_box.x - 50,0 });

	//Game::Instantiate(squareDetectorLeft, Vec2(25, 25));
}

void PawnEnemy::Render() const {

	Vec2 leftPoint = m_associated.m_box.GetCenter() - Vec2(102, m_associated.m_box.y);
	Vec2 rightPoint = m_associated.m_box.GetCenter() + Vec2(102, m_associated.m_box.y);

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

	Rect edgeRect = hitBox.m_box.GetIntersection(otherColl->m_box);

	if (otherObj.tag == "Ground" && !onGround) {
		
		//cout << edgeRect.x << " " << hitBox.m_box.x << endl;
				
		sprite.Open(PAWN_ENEMY_IDLE, 10, 1,.05f);
		SetActionState(IDLE);
		ChangeMovePoint();
		
		onGround = true;
	}
}

void PawnEnemy::Idle(float dt)
{
	waitingTimer.Update(dt);
	if (waitingTimer.Get() > 1.5f /*&& isOnFloor*/)
	{
		sprite.Open(PAWN_ENEMY_MOVE, 10, 1,.05f);
		ChangeMovePoint();
		SetActionState(MOVE);
		waitingTimer.Restart();
	}
}

void PawnEnemy::Move(float dt)
{
	
	if (distanceBetweenPoint <= 1) {
		SetActionState(IDLE);
	}
	else {
		m_associated.m_box.SetCenter(m_associated.m_box.GetCenter() + speed.Normalized() * dt * 100);
	}
}

void PawnEnemy::Attack(float dt)
{
	Vec2 playerPos = player.lock()->m_box.GetCenter();
}

void PawnEnemy::SpecialAttack(float dt)
{
}
