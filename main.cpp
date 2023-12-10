#include "Game.hpp"

int main()
{
	State *menuState = new MenuState();
	Game& game = Game::Instance();

	game.PushState(menuState);
	game.Run();
	delete& game;
	return 0;
}