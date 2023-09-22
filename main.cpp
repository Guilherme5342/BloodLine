#include "Game.h"



int main() {
	State* menuState = new MenuState();
	State* stageState = new StageState();

	Game::Instance().PushState(menuState);
	Game::Instance().Run();
	return 0;
}