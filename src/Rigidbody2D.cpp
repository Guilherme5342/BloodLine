#include "Rigidbody2D.h"

Rigidbody2D::Rigidbody2D(GameObject& associated, float gravityScale) : Component(associated)
{
	this->gravityScale = gravityScale;

}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::Update(float dt)
{
	velocity.y += (mass * gravityScale) * dt;
	
	associated.box.y += velocity.y;
}

void Rigidbody2D::Render()
{
}

