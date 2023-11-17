#pragma once

#include "EnemyBase.hpp"


class PawnEnemy : public EnemyBase {

private:
	float rangeDetection;

	bool invertMove = false;

	Vector2 destination = Vector2(0,0);

public:
	PawnEnemy(GameObject& associated, std::weak_ptr<GameObject> player,Sprite& sprite,int health,int damage, Action enemyAction,EnemyTypePhysics phys, 
		float radius);
	~PawnEnemy();

	inline bool Is(std::string type) {
		return type == "PawnEnemy";
	}

	void Render();
	// Herdado por meio de EnemyBase
	void Idle(float dt);
	void Move(float dt);
	void Attack(float dt);
	void SpecialAttack(float dt);

	inline bool DetectPlayer() {
		return player.lock() != nullptr;
	}
};