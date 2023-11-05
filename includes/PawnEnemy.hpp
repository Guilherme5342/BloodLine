#pragma once

#include "EnemyBase.hpp"


class PawnEnemy : public EnemyBase {

private:
	float rangeDetection;

	std::weak_ptr<GameObject> player;

public:
	PawnEnemy(GameObject associated,std::string filePath,int health,int damage, EnemyTypePhysics phys, 
		float radius,std::weak_ptr<GameObject> player);
	~PawnEnemy();

	void Update(float dt);
	inline bool Is(std::string type) {
		return type == "PawnEnemy";
	}

	// Herdado por meio de EnemyBase
	void Move();
	void Attack();
	void SpecialAttack();
};