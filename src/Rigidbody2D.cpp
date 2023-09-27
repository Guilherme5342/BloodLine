#include "Rigidbody2D.h"

Rigidbody2D::Rigidbody2D(GameObject& associated, float gravityScale) : Component(associated) , gravityScale(gravityScale)
{

}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::Update(float dt)
{
	acceleration.x = (force.x + friction.x) / mass;
	acceleration.y = gravityScale + force.y / mass;

	velocity = acceleration * dt;

	pos = velocity * dt;

	associated.box += pos * acceleration.y;

	//cout << pos * 2000 << endl;
}

void Rigidbody2D::Render()
{
}

