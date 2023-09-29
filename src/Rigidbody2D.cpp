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

	//cout << pos * 2000 << endl;
}

void Rigidbody2D::Render()
{
}

