#include "Galapagos/Components/Rigidbody2D.hpp"
#include "Galapagos/Components/Collider.hpp"

Rigidbody2D::Rigidbody2D(GameObject &m_associated, float mass, float gravityScale)
	: Component(m_associated), m_mass(mass), m_gravityScale(gravityScale)
{
	m_force = Vec2(0, mass * gravityScale);
}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::FixedUpdate(float fdt)
{
	m_acceleration = (m_force / m_mass) * 10;

	m_velocity += m_acceleration * fdt;

	m_associated.m_box.x += m_velocity.x * fdt;
	m_associated.m_box.y += m_velocity.y * fdt;
}

void Rigidbody2D::Update(float dt)
{
}

void Rigidbody2D::NotifyCollision(GameObject &otherObj)
{
	Collider *coll = (Collider *)this->m_associated.GetComponent("Collider");
	Collider *otherColl = (Collider *)otherObj.GetComponent("Collider");

	Rect intersectionRect = coll->m_box.GetIntersection(otherColl->m_box);
	

	if (coll->isTrigger || otherColl->isTrigger)
	{
		return;
	}

	for (std::string label : collisionLabels)
	{
	}

	if ((intersectionRect.w < intersectionRect.h) || ((intersectionRect.w < 1.5f) && (intersectionRect.h < 2.0f)))
	{
		m_hitRight = intersectionRect.x > coll->m_box.x;
		m_hitLeft = !m_hitRight;
		m_associated.m_box.x += (intersectionRect.w + REPULSION_FACTOR) * (m_hitRight ? (-1) : 1);

		m_velocity.x = 0;
	}
	else
	{
		// Batendo em cima / baixo
		if (intersectionRect.y > coll->m_box.y)
		{
			if (m_velocity.y > 0)
			{
				m_velocity.y = 0;
			}
			m_associated.m_box.y -= intersectionRect.h + REPULSION_FACTOR;
		}
		else
		{
			m_associated.m_box.y += intersectionRect.h + REPULSION_FACTOR;
		}
	}
	coll->Update(0);
}

void Rigidbody2D::Render() const
{
}
