#include "Galapagos/Components/RectDebug.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Core/Camera.hpp"

RectDebugger::RectDebugger(GameObject &associated, float x, float y, float w, float h, SDL_Color color) 
    : Component(associated), gameObjectBox(x, y, w, h), color(color)
{
    debugRect = SDL_Rect{(int)gameObjectBox.x, (int)gameObjectBox.y, (int)gameObjectBox.w, (int)gameObjectBox.h};
    associated.m_box = gameObjectBox;
}

RectDebugger::~RectDebugger()
{
}

void RectDebugger::Update(float dt)
{
}

void RectDebugger::Render() const
{
    SDL_Rect rectToFill = SDL_Rect{(int)(gameObjectBox.x - Camera::position.x),
                                   (int)(gameObjectBox.y - Camera::position.y), (int)gameObjectBox.w, (int)gameObjectBox.h};

    SDL_SetRenderDrawColor(Game::GetRenderer(), color.r, color.g, color.b, color.a);

    int rectDrawn = SDL_RenderDrawRect(Game::GetRenderer(), &rectToFill);

    if (rectDrawn != 0)
        std::cout << SDL_GetError() << std::endl;

    SDL_RenderFillRect(Game::GetRenderer(), &rectToFill);
}
