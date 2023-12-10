#pragma once

#define SDL_MAIN_HANDLED

#ifdef _WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stack>
#include <typeinfo>

#include "State.hpp"
#include "StageState.hpp"
#include "MenuState.hpp"

#include "Resources.hpp"

#define MIX_INIT_EVERYTHING (MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC /*| MIX_INIT_MOD*/)
#define FIXED_DELTATIME 0.006f

class Game
{
public:
	static Game &Instance();
	~Game();

	void Run(); // Roda a Lógica do Loop Principal do Jogo

	void CalculateDeltaTime();

	inline void PushState(State *newState) { storedState = newState; }

	inline void ReRender() { SDL_RenderPresent(GetRenderer()); }
	inline float GetDeltaTime() { return this->deltaTime; }

	inline SDL_Renderer *GetRenderer() { return renderer; }
	inline SDL_Window *GetWindow() { return window; }
	inline State &GetState() { return *stateStack.top(); }

	inline int GetWindowWidth() { return windowWidth; }
	inline int GetWindowHeight() { return windowHeight; }
	inline Vector2 GetWindowCenter() { return Vector2(windowWidth, windowHeight) / 2; }

	GameObject *Instantiate(Component *component, Vector2 position);

private:
	static Game *instance;
	Game(string windowName = "Enginhoca", int windowW = 1024, int windowH = 600);

	std::stack<std::unique_ptr<State>> stateStack;

	SDL_Renderer *renderer;
	SDL_Window *window;
	State *storedState;

	int frameStart = 0; // Come�o do Frame do Jogo
	float deltaTime, fixedDeltaTime;

	float leftOver = 0;

	float counter = 0;

	int windowWidth, windowHeight;
};