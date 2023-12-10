#include "Game.hpp"

int main()
{
	State *menuState = new MenuState();
	Game::PushState(menuState);
	Game::Run();
	return 0;
}