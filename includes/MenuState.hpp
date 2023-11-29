#pragma once

#include "State.hpp"
#include "Text.hpp"

#ifdef _WIN32
#define TITLE_IMAGE "assets/img/title.jpg"
#else
#define TITLE_IMAGE "../assets/img/MainMenu.png"
#endif

class MenuState : public State
{

public:
	MenuState();
	~MenuState();
	void LoadAssets();
	void Start();
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
};