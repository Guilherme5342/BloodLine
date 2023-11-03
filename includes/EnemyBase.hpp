#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

#include "Sprite.hpp"
#include "Rigidbody2D.hpp"
#include "HealthHandler.hpp"

#include "GlobalDefinitions.hpp"

class EnemyBase : public Component {

protected:
	Action enemyAction;

	HealthHandler health;
	Rigidbody2D rb;


public:
	EnemyBase(GameObject& associated ,int health, int damage, EnemyTypePhysics enemyPhys);

};

