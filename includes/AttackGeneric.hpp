#pragma once

#include "Component.hpp"
#include "GameObject.hpp"
#include "HealthHandler.hpp"
#include "Collider.hpp"

class AttackGeneric : public Component {

private:
	std::weak_ptr<GameObject> externalAssociated;
	Collider* attackCollider;

public:
	AttackGeneric(GameObject& associated, std::weak_ptr<GameObject> external, Vector2 pos,Vector2 direction);
	~AttackGeneric();

	virtual void PerformAttack();
	


	// Herdado por meio de Component
	virtual void Update(float dt) override;

	virtual void Render() override;

	inline virtual bool Is(std::string type) override {
		return type == "AttackGeneric";
	}

};