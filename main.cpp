#include "Game.hpp"

int main()
{
	State *menuState = new MenuState();
	State *stageState = new StageState();
	Game& game = Game::Instance();

	game.PushState(menuState);
	game.Run();
	delete& game;
	return 0;
}