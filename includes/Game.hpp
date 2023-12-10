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
	~Game();

	inline static void Run() { Game::Instance().__Run(); }// Roda a Lógica do Loop Principal do Jogo
	inline static void PushState(State *newState) { Game::Instance().__PushState(newState); }
	inline static void ReRender() { SDL_RenderPresent(Game::Instance().__GetRenderer()); }
	inline static float GetDeltaTime() { return Game::Instance().__GetDeltaTime(); }
	inline static SDL_Renderer *GetRenderer() { return Game::Instance().__GetRenderer(); }
	inline static SDL_Window *GetWindow() { return Game::Instance().__GetWindow(); }
	inline static State &GetCurrentState() { return Game::Instance().__GetCurrentState(); }
	inline static int GetWindowWidth() { return Game::Instance().__GetWindowWidth(); }
	inline static int GetWindowHeight() { return Game::Instance().__GetWindowHeight(); }
	inline static Vector2 GetWindowCenter() { return Game::Instance().__GetWindowCenter(); }
	inline static GameObject *Instantiate(Component *component, Vector2 position) { return Game::Instance().__Instantiate(component, position); }

	Game(const Game &) = delete;
	Game(Game &&) = delete;
	void operator=(const Game &) = delete;
	void operator=(Game &&) = delete;

private:
	Game(std::string windowName = "Enginhoca", int windowW = 1024, int windowH = 600);

	static Game &Instance();
	static Game *instance;

	void __Run(); // Roda a Lógica do Loop Principal do Jogo
	inline void __PushState(State *newState) { storedState = newState; }
	inline void __ReRender() { SDL_RenderPresent(__GetRenderer()); }
	inline float __GetDeltaTime() { return this->deltaTime; }
	inline SDL_Renderer *__GetRenderer() { return renderer; }
	inline SDL_Window *__GetWindow() { return window; }
	inline State &__GetCurrentState() { return *stateStack.top(); }
	inline int __GetWindowWidth() { return windowWidth; }
	inline int __GetWindowHeight() { return windowHeight; }
	inline Vector2 __GetWindowCenter() { return Vector2(windowWidth, windowHeight) / 2; }
	GameObject *__Instantiate(Component *component, Vector2 position);

	void CalculateDeltaTime();

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