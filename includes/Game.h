#pragma once

#define SDL_MAIN_HANDLED

#include "SDL.h"

#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#ifdef _WIN32
#include "SDL_ttf.h"
#else
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stack>
#include <typeinfo>

#include "State.h"
#include "StageState.h"
#include "MenuState.h"

#include "Resources.h"

#define MIX_INIT_EVERYTHING (MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC /*| MIX_INIT_MOD*/)

class Game
{

private:
	static Game *instance;
	Game(string windowName = "Enginhoca", int windowW = 1024, int windowH = 600);

	std::stack<State *> stateStack;

	SDL_Renderer *renderer;
	SDL_Window *window;
	State *storedState;

	int frameStart = 0; // Come�o do Frame do Jogo
	float deltaTime;

	int windowWidth, windowHeight;

public:
	static Game &Instance();
	~Game();

	SDL_Renderer *GetRenderer();
	SDL_Window *GetWindow();
	State &GetState();

	void Run(); // Roda a L�gica do Loop Principal do Jogo

	void PushState(State *newState);

	inline void ReRender()
	{
		SDL_RenderPresent(GetRenderer());
	}
	inline float GetDeltaTime()
	{
		return this->deltaTime;
	}

	inline void CalculateDeltaTime()
	{
		float currentTime = SDL_GetTicks64();			  // Pega o tempo atual
		deltaTime = (currentTime - frameStart) / 1000.0f; //
		frameStart = currentTime;
	}

	inline int GetWindowWidth()
	{
		return windowWidth;
	}

	inline int GetWindowHeight()
	{
		return windowHeight;
	}

	inline Vector2 GetWindowCenter()
	{
		return Vector2(windowWidth, windowHeight) / 2;
	}
};

inline SDL_Renderer *Game::GetRenderer()
{
	return renderer;
}

inline SDL_Window *Game::GetWindow()
{
	return window;
}

inline State &Game::GetState()
{
	return *stateStack.top();
}

inline void Game::PushState(State *newState)
{
	storedState = newState;
	// cout << "Current State: " << typeid(newState).name() << endl;
}