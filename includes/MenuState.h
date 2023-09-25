#pragma once

#include "State.h"
#include "Text.h"

#define TITLE_IMAGE "assets/img/title.jpg"

class MenuState : public State {

public:
	MenuState();
	
	void LoadAssets();
	void Start();
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

};