#include "PlayerController.hpp"

PlayerController::PlayerController(GameObject &associated, Rigidbody2D &body, int speed) : Component(associated), speed(speed), playerBody(body)
{
	jumping = canJump = false;
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update(float dt)
{

	if (InputSystem::Instance().IsKeyDown(SDLK_a))
	{
		moveDir.x = -speed * dt;
	}
	else if (InputSystem::Instance().IsKeyDown(SDLK_d))
	{
		moveDir.x = speed * dt;
	}
	else
	{
		moveDir.x = 0;
	}
	
	if (InputSystem::Instance().KeyPress(SDLK_SPACE) && canJump)
	{
		playerBody.ApplyForce(Vector2(0, -jumpForce), IMPULSE);
		cout << "Player Jumped" << endl;
		jumping = true;
	}
	else {
		jumping = false;
	}

	// cout << associated.box.x << endl;
	associated.box += moveDir;
}

void PlayerController::Render()
{
}

void PlayerController::NotifyCollision(GameObject& otherObj)
{
	if (otherObj.layer == 1) {
		canJump = true;
	}
	else {
		canJump = false;
	}

	
}
