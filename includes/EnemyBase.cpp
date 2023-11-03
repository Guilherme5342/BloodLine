#include "EnemyBase.hpp"

EnemyBase::EnemyBase(GameObject& associated, int health, int damage, EnemyTypePhysics enemyPhys) :
	Component(associated),
	health(associated,health),
	rb(associated)
{
	switch (enemyPhys)
	{
	case GROUND:
		break;
	case FLY:
		// TODO rb.SetGravity(0)
		break;
	}

}
