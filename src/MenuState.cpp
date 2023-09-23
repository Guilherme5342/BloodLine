#include "MenuState.h"
#include "Game.h"

MenuState::MenuState() : State() {

}

void MenuState::LoadAssets() {
	GameObject* titleObj = new GameObject("Title State");
	Sprite* titleCard = new Sprite(*titleObj, TITLE_IMAGE);

	titleObj->AddComponent(titleCard);

	objectArray.emplace_back(titleObj);

}

void MenuState::Start() {
	StartArray();
}

void MenuState::Update(float dt) {
	InputSystem& input = InputSystem::Instance();

	if (input.KeyPress(SDLK_ESCAPE)) {
		quitRequested = true;
	}
	if (input.KeyPress(SDLK_SPACE)) {
		Game::Instance().PushState(new StageState());
	}

	//UpdateArray(dt);
}

void MenuState::Render() {
	RenderArray();
}


void MenuState::Pause() {

}

void MenuState::Resume() {
	
	Camera::Reset();
	StartArray();
	RenderArray();
}
