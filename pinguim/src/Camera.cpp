#include "Camera.h"
#include "Entity/GameObject.h"
#include "InputManager.h"

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
        speed.x = (InputManager::IsKeyDown(RIGHT_ARROW_KEY) - InputManager::IsKeyDown(LEFT_ARROW_KEY)) * deltaTime * 1000;
        speed.y = -(InputManager::IsKeyDown(UP_ARROW_KEY) - InputManager::IsKeyDown(DOWN_ARROW_KEY)) * deltaTime * 1000;

        position += speed;
    }
}