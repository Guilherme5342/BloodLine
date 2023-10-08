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
	acceleration = force / mass;


	velocity += acceleration * dt;

	//cout << acceleration << endl;
	//cout << velocity << endl;

	associated.box.x += velocity.x * dt;
	associated.box.y += velocity.y * dt;

	cout << associated.box.GetCenter() << endl;
	//if (associated.box.y < MAX_VELOCITY_Y)
	//	associated.box.y = MAX_VELOCITY_Y;

	//force.y = std::clamp(force.y,gravityScale, 2000.0f);
	//force.y -= gravityScale * dt;

	// cout << pos * 2000 << endl;
}

void Rigidbody2D::NotifyCollision(GameObject &otherObj)
{
	Collider *coll = (Collider *)this->associated.GetComponent("Collider");
	Collider *otherColl = (Collider *)otherObj.GetComponent("Collider");

	Rect intersectionRect = coll->box.GetIntersection(otherColl->box);


	// Batendo em cima / baixo
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
