#include "PlayerController.hpp"
#include <cmath> // for std::abs

// Add constants for dash mechanics
const int DASH_SPEED_MULTIPLIER = 5; // Multiplier to the speed during a dash
const float DASH_COOLDOWN = 1.0f;	 // Cooldown time in seconds

PlayerController::PlayerController(GameObject &associated, Sprite &sprite, Rigidbody2D &body, int speed)
	: StateMachine(associated, sprite), speed(speed), playerBody(body)
{
	animState = nullptr;
	canDash = true;	  // Player can initially dash
	dashTimer = 0.0f; // Timer for dash cooldown
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

	// Update the dash timer
	if (!canDash)
	{
		dashTimer += dt;
		if (dashTimer >= DASH_COOLDOWN)
		{
			canDash = true;
			dashTimer = 0.0f;
		}
	}

	// Check for dash input and if dash is available
	if (canDash && InputSystem::Instance().KeyPress(SDLK_LSHIFT))
	{ // Using Left Shift for dash input
		// Apply a dash force, which is a multiple of the normal movement speed, in the direction of movement
		float dashForce = speed * DASH_SPEED_MULTIPLIER;
		moveDir.x += (InputSystem::Instance().IsKeyDown(SDLK_a) - InputSystem::Instance().IsKeyDown(SDLK_d)) * dashForce;
		canDash = false;				   // Start the cooldown
		animState = new DashState(sprite); // Change the animation state to dash
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
