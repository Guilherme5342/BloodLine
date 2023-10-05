#include "PlayerController.hpp"

PlayerController::PlayerController(GameObject &associated, Rigidbody2D &body, int speed) : Component(associated), speed(speed), playerBody(body)
{
	jumping = false;
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

	if (InputSystem::Instance().KeyPress(SDLK_SPACE))
	{
		playerBody.ApplyForce(Vector2(0, -jumpForce));

		jumping = true;
	}

	// cout << associated.box.x << endl;
	associated.box += moveDir;
}

void PlayerController::Render()
{
}
