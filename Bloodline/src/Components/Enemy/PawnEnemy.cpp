#include "PawnEnemy.hpp"
#include "Galapagos/Core/Game.hpp"
#include "GameDefines/GlobalDefinitions.hpp"


PawnEnemy::PawnEnemy(GameObject &m_associated, std::weak_ptr<GameObject> player, int health, int damage,
	Action enemyAction, EnemyTypePhysics phys, float radius) : EnemyBase(m_associated, player, health, damage, enemyAction, phys), m_rangeDetection(radius)
{
}

PawnEnemy::~PawnEnemy()
{
}

void PawnEnemy::Start()
{
	//m_hitBox.SetScale(Vec2(12, 35));
	//m_hitBox.SetOffset({-1, 10});

	//Collider *squareDetectorRight = new Collider(m_associated, {25, 25}, {m_associated.m_box.x + 50, 0});
	//Collider *squareDetectorLeft = new Collider(m_associated, {25, 25}, {-m_associated.m_box.x - 50, 0});

	// Game::Instantiate(squareDetectorLeft, Vec2(25, 25));
}

void PawnEnemy::Render() const {

	Vec2 leftPoint = m_associated.m_box.GetCenter() - Vec2(102, m_associated.m_box.y);
	Vec2 rightPoint = m_associated.m_box.GetCenter() + Vec2(102, m_associated.m_box.y);

	SDL_Point pointLeft = {static_cast<int>(leftPoint.x), static_cast<int>(leftPoint.y)};
	SDL_Point pointRight = {static_cast<int>(rightPoint.x), static_cast<int>(rightPoint.y)};

	SDL_Point offsetPoints[] = {pointLeft, pointRight};

	SDL_SetRenderDrawColor(Game::GetRenderer(), 255, 255, 8, 255);
	SDL_SetRenderDrawBlendMode(Game::GetRenderer(), SDL_BLENDMODE_BLEND);

	SDL_RenderDrawPoints(Game::GetRenderer(), offsetPoints, 2);
}

void PawnEnemy::NotifyCollision(GameObject &otherObj)
{
	Collider *otherColl = (Collider *)otherObj.GetComponent("Collider");

	Rect edgeRect = m_hitBox->m_box.GetIntersection(otherColl->m_box);

	if (otherObj.tag == "Ground" && !m_onGround)
	{

		// cout << edgeRect.x << " " << hitBox.m_box.x << endl;

		m_sprite->Open(PAWN_ENEMY_IDLE, 14, 1, .05f);
		SetActionState(Action::IDLE);
		ChangeMovePoint();

		m_onGround = true;
	}
}

void PawnEnemy::Idle(float dt)
{
	m_waitingTimer.Update(dt);
	if (m_waitingTimer.Get() > 1.5f /*&& isOnFloor*/)
	{
		m_sprite->Open(PAWN_ENEMY_MOVE, 14, 1, .05f);
		ChangeMovePoint();
		SetActionState(Action::MOVE);
		m_waitingTimer.Restart();
	}
}

void PawnEnemy::Move(float dt)
{

	if (m_distanceBetweenPoint <= 1)
	{
		SetActionState(Action::IDLE);
	}
	else
	{
		m_associated.m_box.SetCenter(m_associated.m_box.GetCenter() + m_speed.Normalized() * dt * 100);
	}
}

void PawnEnemy::ChangeMovePoint()
{
	Vec2 pos = m_associated.m_box.GetCenter();

	Vec2 leftPoint = Vec2(-10, 0);
	Vec2 rightPoint = Vec2(10, 0);

	m_destination = !m_invertMove ? leftPoint : rightPoint;
	m_distanceBetweenPoint = pos.Distance(m_destination);
}

void PawnEnemy::Attack(float dt)
{
	Vec2 playerPos = m_player.lock()->m_box.GetCenter();
}

void PawnEnemy::SpecialAttack(float dt)
{
}
