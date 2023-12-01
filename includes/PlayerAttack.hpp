#pragma once

#include "AttackGeneric.hpp"

class PlayerAttack : public AttackGeneric {

public:
	PlayerAttack(GameObject& associated, std::weak_ptr<GameObject> externalAssociated);
	~PlayerAttack();


	// Herdado por meio de Component
	virtual void Update(float dt) override;

	virtual void Render() override;

	virtual bool Is(std::string type) override;

};