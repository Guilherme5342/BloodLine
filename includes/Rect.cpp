#include "Rect.h"
#include "Game.h"

Rect Rect::GetIntersection(Rect& otherRect)
{
    Rect intersection = Rect(std::min(otherRect.x, this->x), std::min(otherRect.y, this->y),0,0);

    return intersection;
}

void Rect::FillRect() {

    SDL_Rect rectToFill = SDL_Rect{ (int)(x - Camera::GetCurrentCamPos().x),(int)(y - Camera::GetCurrentCamPos().y),(int)w,(int)h};
    cout << rectToFill.x << endl;

    SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 255, 255, 255, 255);

    int rectDrawn = SDL_RenderDrawRect(Game::Instance().GetRenderer(), &rectToFill);
  
    if (rectDrawn != 0)
        cout << SDL_GetError() << endl;

    SDL_RenderFillRect(Game::Instance().GetRenderer(), &rectToFill);

    //Game::Instance().GetState().AddObject()
}