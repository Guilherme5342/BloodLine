#include "AttackGeneric.hpp"

AttackGeneric::AttackGeneric(GameObject& associated, std::weak_ptr<GameObject> external,
	Vector2 pos, Vector2 direction) 
	: Component(associated) , externalAssociated(external)
{
	attackCollider = nullptr;
	pos = pos.DirectionFrom(external.lock()->angleDeg);

}

AttackGeneric::~AttackGeneric()
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
