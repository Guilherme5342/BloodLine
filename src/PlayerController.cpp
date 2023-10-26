#include "PlayerController.hpp"

PlayerController::PlayerController(GameObject &associated,Sprite& sprite, Rigidbody2D &body, int speed) 
	: StateMachine(associated,sprite)
	, speed(speed), playerBody(body)
{
	animState = nullptr;
}

PlayerController::~PlayerController()
{
	animState = new DeathState(sprite);
}

void PlayerController::Update(float dt)
{
	
	moving = (!jumping) && (InputSystem::Instance().IsKeyDown(SDLK_a) || InputSystem::Instance().IsKeyDown(SDLK_d));

	moveDir = { 0, 0 };
	moveDir.x += InputSystem::Instance().IsKeyDown(SDLK_a) * (-speed * dt);
	moveDir.x -= InputSystem::Instance().IsKeyDown(SDLK_d) * (-speed * dt);
	
	jumping = InputSystem::Instance().KeyPress(SDLK_SPACE) && canJump;
	playerBody.ApplyForce(Vector2(0, jumping * - jumpForce), IMPULSE);

	// cout << associated.box.x << endl;
	associated.box += moveDir;


	animState = new IdleState(sprite);
	if (moving && canJump) {
		animState = new MovingState(sprite);
	}

	if (InputSystem::Instance().KeyPress(SDLK_z)) {
		animState = new AttackState(sprite,10,30,.2f);
	}

	animState->Update(*this, dt);

	SetState(animState);
}

void PlayerController::NotifyCollision(GameObject& otherObj)
{
	canJump = otherObj.layer == 1;
}

void PlayerController::Render() {
	animState->Render(*this);
}
