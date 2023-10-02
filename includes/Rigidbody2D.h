#pragma once

#include "Component.h"
#include "GameObject.h"

#define MAX_VELOCITY_Y 50.0f

class Rigidbody2D : public Component {


private:
	float mass, gravityScale;
	Vector2 velocity, friction, acceleration, force, pos;

public:
	Rigidbody2D(GameObject& associated, float mass = 1.0f, float gravityScale = 9.81f);
	~Rigidbody2D();

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override {
		return type == "Rigidbody2D";
	}

	virtual void NotifyCollision(GameObject& otherObj) override;

};