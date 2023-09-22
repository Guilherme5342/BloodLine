#include "Camera.h"
#include "InputSystem.h"
#include "Game.h"

GameObject* Camera::focus = nullptr;

Vector2 Camera::pos = (0, 0);

Vector2 Camera::speed = (0, 0);

void Camera::Update(float dt)
{
	if (focus != nullptr) {
		pos = focus->box.GetCenter() - Game::Instance().GetWindowCenter();
		
		return;
	}

	if (InputSystem::Instance().IsKeyDown(SDLK_w)) {
		speed.y = -1;
		cout << speed.y << endl;
	}
	if (InputSystem::Instance().IsKeyDown(SDLK_s)) {
		speed.y = 1;
	}
	if (InputSystem::Instance().IsKeyDown(SDLK_a)) {
		speed.x = -1;
	}
	if (InputSystem::Instance().IsKeyDown(SDLK_d)) {
		speed.x = 1;
	}

	pos.Translate(speed * 200 * dt);
	
	speed = Vector2(0, 0);
}
