#include "Rigidbody2D.h"

Rigidbody2D::Rigidbody2D(GameObject& associated,float mass, float gravityScale) : Component(associated),  mass(mass), gravityScale(gravityScale)
{

}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::Update(float dt)
{
	acceleration.x = (force.x + friction.x) / mass;
	acceleration.y = mass * gravityScale;

	velocity = acceleration * dt;

	//pos = velocity * dt;

	associated.box.x += velocity.x;
	associated.box.y += velocity.y;
	
	if (associated.box.y < MAX_VELOCITY_Y)
		associated.box.y = MAX_VELOCITY_Y;
	
	//cout << pos * 2000 << endl;
}

void Rigidbody2D::NotifyCollision(GameObject& otherObj) {
	Collider* coll = (Collider*)this->associated.GetComponent("Collider");
	Collider* otherColl = (Collider*)otherObj.GetComponent("Collider");

	Rect intersectionRect = coll->box.GetIntersection(otherColl->box);
	
	//if (intersectionRect.w < intersectionRect.h || (intersectionRect.w < 3.0 && intersectionRect.h < 2.0f)) {
	//	hitRight = intersectionRect.x > coll->box.x;

	//}

	if (intersectionRect.y > coll->box.y) {
		acceleration.y = 0;
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


