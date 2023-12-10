#include "Collider.h"
#include <SDL2/SDL.h>

#include "Camera.h"
#include "Game.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated)
{
    m_scale = scale;
    m_offset = offset;
}

void Collider::Update(float deltaTime)
{
    m_box = m_associated.m_box;
    m_box.Scale(m_scale);
    Vec2 rotatedOffset = m_offset.RotatedDeg(m_associated.m_angleDeg);
    m_box.x += rotatedOffset.x;
    m_box.y += rotatedOffset.y;
}

void Collider::Render() const
{
#ifdef DEBUG
    Vec2 center(m_box.GetCenter());
    SDL_Point points[5];

    Vec2 point = (Vec2(m_box.x, m_box.y) - center).RotatedDeg(m_associated.m_angleDeg) + center - Camera::position;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(m_box.x + m_box.w, m_box.y) - center).RotatedDeg(m_associated.m_angleDeg) + center - Camera::position;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(m_box.x + m_box.w, m_box.y + m_box.h) - center).RotatedDeg(m_associated.m_angleDeg) + center - Camera::position;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(m_box.x, m_box.y + m_box.h) - center).RotatedDeg(m_associated.m_angleDeg) + center - Camera::position;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetRenderer(), points, 5);
#endif // DEBUG
}
