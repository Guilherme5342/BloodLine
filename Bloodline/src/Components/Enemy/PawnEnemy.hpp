#pragma once

#include "Components/Enemy/EnemyBase.hpp"

class PawnEnemy : public EnemyBase
{
public:
	PawnEnemy(GameObject &associated, std::weak_ptr<GameObject> player, int health, int damage,
			  Action enemyAction, EnemyTypePhysics phys, float radius);
	~PawnEnemy();

	void Start();
	void Render() const;
	inline bool Is(std::string type) const { return type == "PawnEnemy"; }
	void NotifyCollision(GameObject &otherObj);

	// Herdado por meio de EnemyBase
	void Idle(float dt);
	void Move(float dt);
	void Attack(float dt);
	void SpecialAttack(float dt);

	inline bool DetectPlayer() { return m_player.lock() != nullptr; }

	void ChangeMovePoint();

private:
	float m_rangeDetection;

	bool m_invertMove = false;
	bool m_onGround = false;
	Vec2 m_destination = Vec2(0, 0);
	float m_distanceBetweenPoint = 0;
};