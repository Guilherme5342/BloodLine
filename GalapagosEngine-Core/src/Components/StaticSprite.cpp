#include "Galapagos/Components/StaticSprite.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Core/Resources.hpp"
#include "Galapagos/Core/Camera.hpp"

StaticSprite::StaticSprite(GameObject& associated) : Component(associated)
{
    m_texture = nullptr;
    m_scale = { 1.f, 1.f };

    m_totalWidth = 0;
    m_totalHeight = 0;
    m_clipRect = { 0, 0, 0, 0 };
    m_distRect = { 0, 0, 0, 0 };
}

StaticSprite::StaticSprite(GameObject& associated, std::string filePath, float secondsToSelfDestruct)
    : Component(associated)
{
    m_texture = nullptr;
    Open(filePath);
    m_scale = { 1.f, 1.f };
    m_secondsToSelfDestruct = secondsToSelfDestruct;
}

StaticSprite::~StaticSprite()
{
}

void StaticSprite::Open(std::string filePath)
{
    m_texture = Resources::GetImage(filePath);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_totalWidth, &m_totalHeight);

    m_clipRect = { 0, 0, m_totalWidth, m_totalHeight };
    m_distRect = m_clipRect;

    m_associated.m_box.w = m_totalWidth;
    m_associated.m_box.h = m_totalHeight;
}

void StaticSprite::Update(float deltaTime)
{
    m_selfDestructCount.Update(deltaTime);
    if (m_secondsToSelfDestruct > 0)
    {
        if (m_secondsToSelfDestruct < m_selfDestructCount.Get())
        {
            m_associated.RequestDelete();
        }
    }
}

void StaticSprite::Render() const
{
    Render(m_associated.m_box.x - Camera::position.x, m_associated.m_box.y - Camera::position.y);
}

void StaticSprite::Render(float x, float y) const
{
    SDL_Rect distRect = SDL_Rect{ static_cast<int>(x), static_cast<int>(y), static_cast<int>(m_distRect.w * m_scale.x), static_cast<int>(m_distRect.h * m_scale.y) };
    SDL_RenderCopyEx(Game::GetRenderer(), m_texture, &m_clipRect, &distRect, m_associated.m_angleDeg, nullptr, SDL_FLIP_NONE);
}

std::int32_t StaticSprite::GetWidth() const
{
    return m_totalWidth * m_scale.x;
}

std::int32_t StaticSprite::GetHeight() const
{
    return m_totalHeight * m_scale.y;
}

void StaticSprite::SetScale(float x, float y)
{
    x = ((x != 0) * x) + ((x == 0) * m_scale.x);
    y = ((y != 0) * y) + ((y == 0) * m_scale.y);

    m_scale = { x, y };

    m_associated.m_box.SetSize(GetWidth(), GetHeight());
}

void StaticSprite::SetScale(float x)
{
    SetScale(x, x);
}

void StaticSprite::SetScale(Vec2 scale)
{
    SetScale(scale.x, scale.y);
}