#include "Rigidbody2D.hpp"

Rigidbody2D::Rigidbody2D(GameObject &associated, float mass, float gravityScale)
	: Component(associated), mass(mass), gravityScale(gravityScale)
{
	force = Vector2(0, mass * gravityScale);
}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::FixedUpdate(float fdt)
{
	acceleration = (force / mass) * 10;

	velocity += acceleration * fdt;

	associated.box.x += velocity.x * fdt;
	associated.box.y += velocity.y * fdt;
}

void Rigidbody2D::Update(float dt)
{
	
}

void Rigidbody2D::NotifyCollision(GameObject &otherObj)
{
	Collider *coll = (Collider *)this->associated.GetComponent("Collider");
	Collider *otherColl = (Collider *)otherObj.GetComponent("Collider");

	Rect intersectionRect = coll->box.GetIntersection(otherColl->box);

	if (coll->IsTrigger() || otherColl->IsTrigger()) {
		return;
	}

	for (std::string label : collisionLabels) {
		
	}

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
			if (velocity.y > 0) {
				velocity.y = 0;
			}
			associated.box.y -= intersectionRect.h + REPULSION_FACTOR;
		}
		else
		{
			associated.box.y += intersectionRect.h + REPULSION_FACTOR;
		}
	}
	coll->Update(0);
}

void Rigidbody2D::NotifyNoCollision(GameObject& otherObj) {
	hitUp = false;
	hitDown = false;
	hitLeft = false;
	hitRight = false;
}
void Rigidbody2D::Render()
{
}
