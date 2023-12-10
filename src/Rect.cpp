#include "Rect.hpp"
#include "Game.hpp"

Rect Rect::GetIntersection(Rect &otherRect)
{
    Rect intersection = Rect(std::max(otherRect.x, this->x), std::max(otherRect.y, this->y), 0, 0);

    intersection.SetSize(std::min(this->x + this->w, otherRect.x + otherRect.w) - intersection.x,
                         std::min(this->y + this->h, otherRect.y + otherRect.h) - intersection.y);
    return intersection;
}

void Rect::FillRect()
{

    SDL_Rect rectToFill = SDL_Rect{(int)(x - Camera::GetCurrentCamPos().x), (int)(y - Camera::GetCurrentCamPos().y), (int)w, (int)h};
    std::cout << rectToFill.x << std::endl;

    SDL_SetRenderDrawColor(Game::GetRenderer(), 255, 255, 255, 255);

    int rectDrawn = SDL_RenderDrawRect(Game::GetRenderer(), &rectToFill);

    if (rectDrawn != 0)
        std::cout << SDL_GetError() << std::endl;

    SDL_RenderFillRect(Game::GetRenderer(), &rectToFill);

    // Game::GetState().AddObject()
}