#include "RectDebug.hpp"
#include "Game.hpp"

RectDebugger::RectDebugger(GameObject &associated, float x, float y, float w, float h, SDL_Color color) 
    : Component(associated), gameObjectBox(x, y, w, h), color(color)
{
    debugRect = SDL_Rect{(int)gameObjectBox.x, (int)gameObjectBox.y, (int)gameObjectBox.w, (int)gameObjectBox.h};
    associated.box = gameObjectBox;
}

RectDebugger::~RectDebugger()
{
}

void RectDebugger::Update(float dt)
{
}

void RectDebugger::Render()
{
    SDL_Rect rectToFill = SDL_Rect{(int)(gameObjectBox.x - Camera::GetCurrentCamPos().x),
                                   (int)(gameObjectBox.y - Camera::GetCurrentCamPos().y), (int)gameObjectBox.w, (int)gameObjectBox.h};

    SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), color.r, color.g, color.b, color.a);

    int rectDrawn = SDL_RenderDrawRect(Game::Instance().GetRenderer(), &rectToFill);

    if (rectDrawn != 0)
        cout << SDL_GetError() << endl;

    SDL_RenderFillRect(Game::Instance().GetRenderer(), &rectToFill);
}
