#pragma once

#include "AttackGeneric.hpp"
#include "InputSystem.hpp"


class PlayerAttack : public AttackGeneric {

public:
	PlayerAttack(GameObject& associated, std::weak_ptr<GameObject> externalAssociated, Vector2 pos, Vector2 direction);
	~PlayerAttack();

	void Start();
	// Herdado por meio de Component
	virtual void Update(float dt) override;

	virtual void Render() override;

	virtual bool Is(std::string type) override;

	void PerformAttack();
};