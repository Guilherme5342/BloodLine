#pragma once

#include <memory>
#include <unordered_map>

#include "Command.hpp"

#ifdef _WIN32
#include "SDL_events.h"
#else
#include <SDL2/SDL_events.h>
#endif

class InputSystem
{
public:
	inline static void Update() { InputSystem::Instance().__Update(); }
	inline static bool KeyPress(int keyEnum) { return InputSystem::Instance().__KeyPress(keyEnum); }
	inline static bool KeyRelease(int keyEnum) { return InputSystem::Instance().__KeyRelease(keyEnum); }
	inline static bool IsKeyDown(int keyEnum) { return InputSystem::Instance().__IsKeyDown(keyEnum); }
	inline static bool MousePress(int button) { return InputSystem::Instance().__MousePress(button); }
	inline static bool MouseRelease(int button) { return InputSystem::Instance().__MouseRelease(button); }
	inline static bool IsMouseDown(int button) { return InputSystem::Instance().__IsMouseDown(button); }
	inline static int GetMouseX() { return InputSystem::Instance().mouseX; }
	inline static int GetMouseY() { return InputSystem::Instance().mouseY; }
	inline static int GetCurrentKey() { return InputSystem::Instance().currentKey; }
	inline static bool QuitRequested() { return InputSystem::Instance().quitRequested; }

	InputSystem(const InputSystem &) = delete;
	InputSystem(InputSystem &&) = delete;
	void operator=(const InputSystem &) = delete;
	void operator=(InputSystem &&) = delete;

private:
	static InputSystem &Instance();

	void __Update();

	inline bool __KeyPress(int keyEnum) { return __IsKeyDown(keyEnum) == true && (keyUpdate[keyEnum] == updateCounter); }
	inline bool __KeyRelease(int keyEnum) { return __IsKeyDown(keyEnum) == false && (keyUpdate[keyEnum] == updateCounter); }
	inline bool __IsKeyDown(int keyEnum) { return keyState[keyEnum]; }
	inline bool __MousePress(int button) { return mouseState[button] && (mouseUpdate[button] == updateCounter); }
	inline bool __MouseRelease(int button) { return __IsMouseDown(button) == false && (mouseUpdate[button] == updateCounter); }
	inline bool __IsMouseDown(int button) { return mouseState[button]; }

	bool mouseState[6];
	int mouseUpdate[6];

	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

	int updateCounter;

	bool quitRequested;

	int mouseX, mouseY;

	int currentKey;

	InputSystem();
	~InputSystem();

	Command *buttonSpace;
	Command *buttonAlpha1;
	Command *buttonAlpha2;

	Command *HandleInput();
};