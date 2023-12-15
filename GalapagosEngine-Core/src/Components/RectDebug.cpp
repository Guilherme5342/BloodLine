#include "Galapagos/Components/RectDebug.hpp"

#include <stdint.h>

#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Core/Camera.hpp"

RectDebugger::RectDebugger(GameObject &associated, float x, float y, float w, float h, SDL_Color color)
    : Component(associated), m_gameObjectBox(x, y, w, h), m_color(color)
{
    m_debugRect = SDL_Rect{static_cast<std::int32_t>(m_gameObjectBox.x),
                           static_cast<std::int32_t>(m_gameObjectBox.y),
                           static_cast<std::int32_t>(m_gameObjectBox.w),
                           static_cast<std::int32_t>(m_gameObjectBox.h)};

    associated.m_box = m_gameObjectBox;
}

RectDebugger::~RectDebugger()
{
}

void RectDebugger::Update(float dt)
{
}

void RectDebugger::Render() const
{
#ifdef DEBUG
    SDL_Rect rectToFill = SDL_Rect{static_cast<std::int32_t>(m_gameObjectBox.x - Camera::position.x),
                                   static_cast<std::int32_t>(m_gameObjectBox.y - Camera::position.y),
                                   static_cast<std::int32_t>(m_gameObjectBox.w),
                                   static_cast<std::int32_t>(m_gameObjectBox.h)};

    SDL_SetRenderDrawColor(Game::GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);

    int rectDrawn = SDL_RenderDrawRect(Game::GetRenderer(), &rectToFill);

    if (rectDrawn != 0)
        std::cout << SDL_GetError() << std::endl;

    SDL_RenderFillRect(Game::GetRenderer(), &rectToFill);
#endif // DEBUG
}
