#include "RectDebug.h"
#include "Game.h"

RectDebugger::RectDebugger(GameObject& associated, float x, float y, float w,float h) : Component(associated) , gameObjectBox(x,y,w,h)
{
	debugRect = SDL_Rect{ (int)gameObjectBox.x, (int)gameObjectBox.y, (int)gameObjectBox.w,(int)gameObjectBox.h };
}

void RectDebugger::Update(float dt)
{

}

void RectDebugger::Render()
{
    SDL_Rect rectToFill = SDL_Rect{ (int)(gameObjectBox.x - Camera::GetCurrentCamPos().x),
        (int)(gameObjectBox.y - Camera::GetCurrentCamPos().y),(int)gameObjectBox.w,(int)gameObjectBox.h };

    SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 255, 255, 255, 255);

    int rectDrawn = SDL_RenderDrawRect(Game::Instance().GetRenderer(), &rectToFill);

    if (rectDrawn != 0)
        cout << SDL_GetError() << endl;

    SDL_RenderFillRect(Game::Instance().GetRenderer(), &rectToFill);
}

