#pragma once

#include "Components/Enemy/EnemyBase.hpp"


class PawnEnemy : public EnemyBase {

private:
	float rangeDetection;

	bool invertMove = false;

	Vec2 destination = Vec2(0,0);
	float distanceBetweenPoint = 0;

public:
	PawnEnemy(GameObject& associated, std::weak_ptr<GameObject> player,Sprite& sprite,int health,int damage, 
		Action enemyAction,EnemyTypePhysics phys, float radius);
	~PawnEnemy();

	void Start();
	inline bool Is(std::string type) {
		return type == "PawnEnemy";
	}
	void Render();
	void NotifyCollision(GameObject& otherObj);

	// Herdado por meio de EnemyBase
	void Idle(float dt);
	void Move(float dt);
	void Attack(float dt);
	void SpecialAttack(float dt);

	inline bool DetectPlayer() {
		return player.lock() != nullptr;
	}

	inline void ChangeMovePoint() {
		Vec2 pos = m_associated.m_box.GetCenter();

		Vec2 leftPoint = pos.RotatedDeg(270);
		Vec2 rightPoint = pos.RotatedDeg(0);

		destination = !invertMove ? leftPoint : rightPoint;
		//distanceBetweenPoint = Distance(pos, destination);

	}
};