#include "Galapagos/Core/Camera.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"

Vec2 Camera::position = {0, 0};
Vec2 Camera::speed = {0, 0};
GameObject *Camera::m_focus = nullptr;

void Camera::Follow(GameObject *newFocus)
{
    m_focus = newFocus;
}

void Camera::Unfollow()
{
    m_focus = nullptr;
}

void Camera::Update(float deltaTime)
{
    if (m_focus)
    {
        position = m_focus->m_box.GetCenter();
        position += Vec2{1024 / -2, 600 / -2};
    }
    else
    {
        speed.x = (InputManager::IsKeyDown(Key::ArrowRight) - InputManager::IsKeyDown(Key::ArrowLeft)) * deltaTime * 1000;
        speed.y = -(InputManager::IsKeyDown(Key::ArrowUp) - InputManager::IsKeyDown(Key::ArrowDown)) * deltaTime * 1000;

        position += speed;
    }
}

void Camera::Reset()
{
    position = Vec2(0,0);
}
