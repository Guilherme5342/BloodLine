#include "PlayerController.hpp"

PlayerController::PlayerController(GameObject &associated, Rigidbody2D &body, int speed) : Component(associated), speed(speed), playerBody(body)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update(float dt)
{
	moveDir = { 0, 0 };
	moveDir.x += InputSystem::Instance().IsKeyDown(SDLK_a) * (-speed * dt);
	moveDir.x -= InputSystem::Instance().IsKeyDown(SDLK_d) * (-speed * dt);
	
	jumping = InputSystem::Instance().KeyPress(SDLK_SPACE) && canJump;
	playerBody.ApplyForce(Vector2(0, jumping * - jumpForce), IMPULSE);

	// cout << associated.box.x << endl;
	associated.box += moveDir;
}

void PlayerController::Render()
{
}

void PlayerController::NotifyCollision(GameObject& otherObj)
{
	canJump = otherObj.layer == 1;
}
