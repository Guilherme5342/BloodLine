#include "Sprite.h"

#include <SDL2/SDL_image.h>
#include <iostream>

#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    m_texture = nullptr;
    m_scale = {1.f, 1.f};
    m_frameCount = 1;
    m_currentFrame = 1;
}
Sprite::Sprite(GameObject &associated, std::string filePath, std::uint32_t frameCount, float frameTime, bool loop, float secondsToSelfDestruct) : Component(associated)
{
    m_texture = nullptr;
    Open(filePath, frameCount, frameTime);
    m_scale = {1.f, 1.f};
    m_loop = loop;
    m_secondsToSelfDestruct = secondsToSelfDestruct;
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string filePath, std::uint32_t frameCount, float frameTime)
{
    m_frameCount = frameCount;
    m_frameTime = frameTime;
    m_timeElapsed = 0;
    m_currentFrame = 1;

    m_texture = Resources::GetImage(filePath);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

    m_clipRect = {0, 0, m_width / static_cast<std::int32_t>(frameCount), m_height};

    m_associated.m_box.w = m_width / static_cast<std::int32_t>(frameCount);
    m_associated.m_box.h = m_height;
}

void Sprite::SetClip(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h)
{
    m_clipRect = {x, y, w, h};
}

void Sprite::Update(float deltaTime)
{
    m_selfDestructCount.Update(deltaTime);
    if(m_secondsToSelfDestruct > 0){
        if(m_secondsToSelfDestruct < m_selfDestructCount.Get()){
            m_associated.RequestDelete();
        }
    }
    m_timeElapsed += deltaTime;
    if ((m_timeElapsed > m_frameTime) && (m_frameCount > 1) && (m_currentFrame != m_frameCount || m_loop))
    {
        m_currentFrame++;
        m_currentFrame -= (m_currentFrame > m_frameCount) * m_frameCount;
        m_clipRect.x = (m_currentFrame - 1) * GetWidth();
        m_timeElapsed = 0;
    }
}

void Sprite::Render() const
{
    Render(m_associated.m_box.x - Camera::position.x, m_associated.m_box.y - Camera::position.y);
}

void Sprite::Render(float x, float y) const
{
    SDL_Rect distRect = SDL_Rect{static_cast<int>(x), static_cast<int>(y), static_cast<int>(m_clipRect.w * m_scale.x), static_cast<int>(m_clipRect.h * m_scale.y)};
    SDL_RenderCopyEx(Game::GetRenderer(), m_texture, &m_clipRect, &distRect, m_associated.m_angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Sprite::Is(std::string type) const
{
    return type == "Sprite";
}

std::int32_t Sprite::GetWidth() const
{
    return m_width / static_cast<std::int32_t>(m_frameCount) * m_scale.x;
}

std::int32_t Sprite::GetHeight() const
{
    return m_height * m_scale.y;
}

bool Sprite::IsOpen() const
{
    return m_texture != nullptr;
}

void Sprite::SetScale(float x, float y)
{
    x = ((x != 0) * x) + ((x == 0) * m_scale.x);
    y = ((y != 0) * y) + ((y == 0) * m_scale.y);

    m_associated.m_box.Scale(x, y);

    m_scale = {x, y};
}

void Sprite::SetScale(float x)
{
    SetScale(x, x);
}

void Sprite::SetScale(Vec2 scale)
{
    SetScale(scale.x, scale.y);
}

void Sprite::SetFrame(std::uint32_t frame)
{
    frame += (frame == 0);
    m_currentFrame = frame % m_frameCount;
}

void Sprite::SetFrameCount(std::uint32_t frameCount)
{
    m_frameCount = frameCount;
    m_currentFrame = 0;
}

void Sprite::SetFrameTime(float frameTime)
{
    m_frameTime = frameTime;
}

Vec2 Sprite::GetScale() const
{
    return m_scale;
}