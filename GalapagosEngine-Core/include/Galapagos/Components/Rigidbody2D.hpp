#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"

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
	Vec2 velocity, friction, acceleration, force, position;

	bool jumping;

	bool hitRight, hitLeft, hitDown, hitUp;

	std::vector<std::string> collisionLabels;

public:
	Rigidbody2D(GameObject &associated, float mass = 1.0f, float gravityScale = 9.81f);
	~Rigidbody2D();

	// Herdado por meio de Component
	virtual void FixedUpdate(float fixedDt) override;
	virtual void Update(float dt) override;
	void Render() const override;

	inline virtual bool Is(std::string type) const override
	{
		return type == "Rigidbody2D";
	}

	virtual void NotifyCollision(GameObject &otherObj) override;
	//virtual void NotifyNoCollision(GameObject &otherObj) override;

	inline void ApplyVelocity(Vec2 velocity)
	{
		this->velocity += velocity;
	}

	inline void ApplyForce(Vec2 force, ForceType forceType = ForceType::FORCE)
	{
		velocity += force * forceType;
		force = Vec2(0, mass * (gravityScale * 10));
	}

	inline bool HitUp() {return hitUp;}
	inline bool HitDown() {return hitDown;}
	inline bool HitLeft() {return hitLeft;}
	inline bool HitRight() {return hitRight;}
};