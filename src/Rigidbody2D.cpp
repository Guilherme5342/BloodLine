#include "Rigidbody2D.hpp"

Rigidbody2D::Rigidbody2D(GameObject &associated, float mass, float gravityScale) : Component(associated), mass(mass), gravityScale(gravityScale)
{
	force = Vector2(0, mass * gravityScale);
}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::Update(float dt)
{
	acceleration = (force / mass);

	velocity += acceleration * dt;

	associated.box.x += velocity.x * dt;
	associated.box.y += velocity.y * dt;
}

void Rigidbody2D::NotifyCollision(GameObject &otherObj)
{
	Collider *coll = (Collider *)this->associated.GetComponent("Collider");
	Collider *otherColl = (Collider *)otherObj.GetComponent("Collider");

	Rect intersectionRect = coll->box.GetIntersection(otherColl->box);

	if ((intersectionRect.w < intersectionRect.h) || ((intersectionRect.w < 1.5f) && (intersectionRect.h < 2.0f)))
	{
		hitRight = intersectionRect.x > coll->box.x;
		hitLeft = !hitRight;
		associated.box.x += (intersectionRect.w + REPULSION_FACTOR) * (hitRight ?  (- 1) : 1);

		velocity.x = 0;
	}
	else 
	{
		// Batendo em cima / baixo
		if (intersectionRect.y > coll->box.y)
		{
			velocity.y = 0;
			associated.box.y -= intersectionRect.h + REPULSION_FACTOR;
		}
		else
		{
			associated.box.y += intersectionRect.h + REPULSION_FACTOR;
		}
	}
	coll->Update(0);
}

void Rigidbody2D::Render()
{
}
