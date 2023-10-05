#include "Rigidbody2D.hpp"

Rigidbody2D::Rigidbody2D(GameObject &associated, float mass, float gravityScale) : Component(associated), mass(mass), gravityScale(gravityScale)
{
}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::Update(float dt)
{
	acceleration.x = (force.x + friction.x) / mass;
	acceleration.y = (mass * gravityScale) + (force.y);

	velocity = acceleration * dt;

	// pos = velocity * dt;

	associated.box.x += velocity.x;
	associated.box.y += velocity.y;

	if (associated.box.y < MAX_VELOCITY_Y)
		associated.box.y = MAX_VELOCITY_Y;

	force.y = std::clamp(force.y, 1.f, 2000.0f);
	force.y -= dt;

	// cout << pos * 2000 << endl;
}

void Rigidbody2D::NotifyCollision(GameObject &otherObj)
{
	Collider *coll = (Collider *)this->associated.GetComponent("Collider");
	Collider *otherColl = (Collider *)otherObj.GetComponent("Collider");

	Rect intersectionRect = coll->box.GetIntersection(otherColl->box);

	if (intersectionRect.y > coll->box.y)
	{
		velocity.y = 0;
		associated.box.y -= intersectionRect.h + .5f;
	}
	else
	{
		associated.box.y += intersectionRect.h + .5f;
	}
	//->Update(0);
}

void Rigidbody2D::Render()
{
}
