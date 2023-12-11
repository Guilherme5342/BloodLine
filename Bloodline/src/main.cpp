#define SDL_MAIN_HANDLED
#include "Galapagos/Core/Game.h"
#include "States/TitleState.h"

int main(int argc, const char **argv)
{
    Game::Push(new TitleState() );
    Game::Run();
    return 0;
}
