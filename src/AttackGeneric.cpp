#include "AttackGeneric.hpp"

AttackGeneric::AttackGeneric(GameObject& associated, std::weak_ptr<GameObject> external,
	Vector2 pos, Vector2 direction) 
	: Component(associated) , externalAssociated(external)
{

	pos = pos.DirectionFrom(external.lock()->angleDeg);

	attackCollider = new Collider(associated,{2,2},pos + direction, true,true);

}

AttackGeneric::~AttackGeneric()
{
}

void AttackGeneric::PerformAttack()
{
}

void AttackGeneric::Update(float dt)
{
	if (externalAssociated.expired()) {
		return;
	}

}

void AttackGeneric::Render()
{
}
