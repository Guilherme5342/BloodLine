#include "Camera.hpp"
#include "InputSystem.hpp"
#include "Game.hpp"

GameObject *Camera::focus = nullptr;

Vector2 Camera::pos = Vector2(0, 0);

Vector2 Camera::speed = Vector2(0, 0);

void Camera::Update(float dt)
{
	if (focus != nullptr)
	{
		pos = focus->box.GetCenter() - Game::GetWindowCenter();

		return;
	}

	if (InputSystem::Instance().IsKeyDown(SDLK_w))
	{
		speed.y = -1;
		// cout << speed.y << endl;
	}
	if (InputSystem::Instance().IsKeyDown(SDLK_s))
	{
		speed.y = 1;
	}
	if (InputSystem::Instance().IsKeyDown(SDLK_a))
	{
		speed.x = -1;
	}
	if (InputSystem::Instance().IsKeyDown(SDLK_d))
	{
		speed.x = 1;
	}

	pos.Translate(speed * 200 * dt);
	// cout << pos << endl;
	speed.x = 0;
	speed.y = 0;
}
