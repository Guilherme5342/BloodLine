#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

#define REPULSION_FACTOR 1e-4

#define WEIGHT_GRAVITY(m) m * 9.81f

const float damping = 0.95f;

enum ForceType
{
	FORCE = 1,
	IMPULSE = 10
};

class Rigidbody2D : public Component
{

private:
	float mass, gravityScale;
	Vector2 velocity, friction, acceleration, force, position;

	bool jumping;

	bool hitRight, hitLeft, hitDown, hitUp;

public:
	Rigidbody2D(GameObject &associated, float mass = 1.0f, float gravityScale = 9.81f);
	~Rigidbody2D();

	// Herdado por meio de Component
	virtual void FixedUpdate(float fixedDt) override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override
	{
		return type == "Rigidbody2D";
	}

	virtual void NotifyCollision(GameObject &otherObj) override;

	inline void ApplyVelocity(Vector2 velocity)
	{
		this->velocity += velocity;
	}

	inline void ApplyForce(Vector2 force, ForceType forceType = ForceType::FORCE)
	{
		velocity += force * forceType;
		force = Vector2(0, mass * (gravityScale * 10));
	}
};