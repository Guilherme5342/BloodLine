#define SDL_MAIN_HANDLED

#include "Galapagos/Core/Game.hpp"
#include "States/TitleState.hpp"

int main(int argc, const char **argv)
{
    Game::Push(new TitleState() );
    Game::Run();
    return 0;
}
