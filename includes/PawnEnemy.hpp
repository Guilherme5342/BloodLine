#pragma once

#include "EnemyBase.hpp"


class PawnEnemy : public EnemyBase {

private:
	float rangeDetection;

	bool invertMove = false;

public:
	PawnEnemy(GameObject associated, std::weak_ptr<GameObject> player,std::string filePath,int health,int damage, Action enemyAction,EnemyTypePhysics phys, 
		float radius);
	~PawnEnemy();

	inline bool Is(std::string type) {
		return type == "PawnEnemy";
	}

	// Herdado por meio de EnemyBase
	void Idle();
	void Move();
	void Attack();
	void SpecialAttack();

	inline bool DetectPlayer() {
		return player.lock() != nullptr;
	}
};