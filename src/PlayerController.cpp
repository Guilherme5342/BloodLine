#include "PlayerController.hpp"
#include <cmath>

const int DASH_SPEED_MULTIPLIER = 1000;
const float DASH_COOLDOWN = 2.0f;
const float DASH_DURATION = 0.2f;

PlayerController::PlayerController(GameObject &associated, Sprite &sprite, Rigidbody2D &body, int speed)
	: StateMachine(associated, sprite),
	  speed(speed), playerBody(body)
{
	animState = nullptr;
	canDash = true;
	dashTimer = 0.0f;
	dashElapsedTime = 0.0f;
}

PlayerController::~PlayerController()
{
	animState = new DeathState(sprite);
}

void PlayerController::Update(float dt)
{

	moving = (!jumping) && (InputSystem::Instance().IsKeyDown(SDLK_a) || InputSystem::Instance().IsKeyDown(SDLK_d));

	moveDir = {0, 0};
	moveDir.x += InputSystem::Instance().IsKeyDown(SDLK_a) * (-speed * dt);
	moveDir.x -= InputSystem::Instance().IsKeyDown(SDLK_d) * (-speed * dt);

	jumping = InputSystem::Instance().KeyPress(SDLK_SPACE) && canJump;
	playerBody.ApplyForce(Vector2(0, jumping * -jumpForce), IMPULSE);

	int dashDirection = InputSystem::Instance().IsKeyDown(SDLK_a) ? -1 : InputSystem::Instance().IsKeyDown(SDLK_d) ? 1
																												   : 0;
	float dashVelocity = DASH_SPEED_MULTIPLIER * dashDirection;

	if (canDash && InputSystem::Instance().KeyPress(SDLK_LSHIFT))
	{

		playerBody.ApplyVelocity(Vector2(dashVelocity, 0));
		canDash = false;
		dashElapsedTime = 0.0f;
		animState = new DashState(sprite);
	}

	if (!canDash)
	{
		dashElapsedTime += dt;
		if (dashElapsedTime >= DASH_DURATION)
		{

			playerBody.ApplyVelocity(Vector2(-dashVelocity, 0));
			canDash = true;
			dashTimer = 0.0f;
		}
	}

	// cout << associated.box.x << endl;
	associated.box += moveDir;

	animState = new IdleState(sprite);
	if (moving && canJump)
	{
		animState = new MovingState(sprite);
	}

	if (InputSystem::Instance().KeyPress(SDLK_z))
	{
		animState = new AttackState(sprite, 10, 30, .2f);
	}

	animState->Update(*this, dt);

	SetState(animState);
}

void PlayerController::NotifyCollision(GameObject &otherObj)
{
	canJump = otherObj.layer == 1;
}

void PlayerController::Render()
{
	animState->Render(*this);
}
