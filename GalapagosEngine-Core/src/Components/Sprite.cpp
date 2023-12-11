#include "Galapagos/Components/Sprite.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Core/Resources.hpp"
#include "Galapagos/Core/Camera.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    m_texture = nullptr;
    m_scale = {1.f, 1.f};
    m_rowCount = 1;
    m_columnCount = 1;
    m_currentFrame = 1;

    m_totalWidth = 0;
    m_totalHeight = 0;
    m_clipRect = {0, 0, 0, 0};
    m_distRect = {0, 0, 0, 0};
}

Sprite::Sprite(GameObject& associated, std::string filePath) : Component (associated)
{
    m_texture = nullptr;
    Open(filePath, 1, 1, 1);
    m_scale = { 1.f, 1.f };
    m_loop = true;
    m_secondsToSelfDestruct = 0;
}

Sprite::Sprite(GameObject& associated, std::string filePath, std::uint32_t frameCount, float frameTime, bool loop)
    : Component(associated)
{
    m_texture = nullptr;
    m_frameCount = frameCount;
    Open(filePath, frameCount, 1, frameTime);
    m_scale = { 1.f, 1.f };
    m_loop = loop;
    m_secondsToSelfDestruct = 0;
}

Sprite::Sprite(GameObject& associated, std::string filePath, std::uint32_t frameCount, float frameTime, bool loop, std::uint32_t columnCount, std::uint32_t rowCount, float secondsToSelfDestruct )
    : Component(associated)
{
    m_texture = nullptr;
    m_frameCount = frameCount;
    Open(filePath, columnCount, rowCount, frameTime);
    m_scale = { 1.f, 1.f };
    m_loop = loop;
    m_secondsToSelfDestruct = secondsToSelfDestruct;
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string filePath, std::uint32_t columnCount, std::uint32_t rowCount, float frameTime)
{
    m_columnCount = columnCount;
    m_rowCount = rowCount;
    m_frameTime = frameTime;
    m_timeElapsed = 0;
    m_currentFrame = 1;

    m_texture = Resources::GetImage(filePath);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_totalWidth, &m_totalHeight);

    m_frameWidth = m_totalWidth / static_cast<std::int32_t>(m_columnCount);
    m_frameHeight = m_totalHeight / static_cast<std::int32_t>(m_rowCount);

    m_clipRect = {0, 0, m_frameWidth, m_frameHeight};
    m_distRect = m_clipRect;

    m_associated.m_box.w = m_frameWidth;
    m_associated.m_box.h = m_frameHeight;
}

void Sprite::SetClip(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h)
{
    m_clipRect = {x, y, w, h};
}

void Sprite::SetDist(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h)
{
    m_distRect = { x, y, w, h };
}

void Sprite::Update(float deltaTime)
{
    m_selfDestructCount.Update(deltaTime);
    if (m_secondsToSelfDestruct > 0)
    {
        if (m_secondsToSelfDestruct < m_selfDestructCount.Get())
        {
            m_associated.RequestDelete();
        }
    }
    m_timeElapsed += deltaTime;
    if ((m_timeElapsed > m_frameTime) && (m_frameCount > 1) && (m_currentFrame != m_frameCount || m_loop))
    {
        m_currentFrame++;
        m_currentFrame -= (m_currentFrame > m_frameCount) * m_frameCount;
        m_clipRect.x = ((m_currentFrame - 1) % m_columnCount) * m_frameWidth;
        m_clipRect.y = ((m_currentFrame - 1) / m_columnCount) * m_frameHeight;
        m_timeElapsed = 0;
    }
}

void Sprite::Render() const
{
    Render(m_associated.m_box.x - Camera::position.x, m_associated.m_box.y - Camera::position.y);
}

void Sprite::Render(float x, float y) const
{
    SDL_Rect distRect = SDL_Rect{static_cast<int>(x), static_cast<int>(y), static_cast<int>(m_distRect.w * m_scale.x), static_cast<int>(m_distRect.h * m_scale.y)};
    SDL_RenderCopyEx(Game::GetRenderer(), m_texture, &m_clipRect, &distRect, m_associated.m_angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Sprite::Is(std::string type) const
{
    return type == "Sprite";
}

std::int32_t Sprite::GetWidth() const
{
    return m_frameWidth * m_scale.x;
}

std::int32_t Sprite::GetHeight() const
{
    return m_frameHeight * m_scale.y;
}

bool Sprite::IsOpen() const
{
    return m_texture != nullptr;
}

void Sprite::SetScale(float x, float y)
{
    x = ((x != 0) * x) + ((x == 0) * m_scale.x);
    y = ((y != 0) * y) + ((y == 0) * m_scale.y);

    m_scale = {x, y};

    m_associated.m_box.SetSize(GetWidth(), GetHeight());
}

void Sprite::SetScale(float x)
{
    SetScale(x, x);
}

void Sprite::SetScale(Vec2 scale)
{
    SetScale(scale.x, scale.y);
}

Vec2 Sprite::GetScale() const
{
    return m_scale;
}