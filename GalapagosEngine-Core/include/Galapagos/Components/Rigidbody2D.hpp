#pragma once

#include "Galapagos/Core/Component.hpp"

#define REPULSION_FACTOR 1e-4

#define WEIGHT_GRAVITY(m) m * 9.81f

const float damping = 0.95f;

enum class ForceType
{
	FORCE = 1,
	IMPULSE = 10
};

class Rigidbody2D : public Component
{
public:
	Rigidbody2D(GameObject &associated, float mass = 1.0f, float gravityScale = 9.81f);
	~Rigidbody2D();

	// Herdado por meio de Component
	virtual void FixedUpdate(float fixedDt) override;
	virtual void Update(float dt) override;
	void Render() const override;

	inline virtual bool Is(std::string type) const override { return type == "Rigidbody2D"; }

	virtual void NotifyCollision(GameObject &otherObj) override;

	inline void ApplyVelocity(Vec2 velocity) { this->m_velocity += velocity; }

	void ApplyForce(Vec2 force, ForceType forceType = ForceType::FORCE);

private:
	float m_mass, m_gravityScale;
	Vec2 m_velocity, m_friction, m_acceleration, m_force, m_position;

	bool m_jumping;

	bool m_hitRight, m_hitLeft, m_hitDown, m_hitUp;

	std::vector<std::string> collisionLabels;
};