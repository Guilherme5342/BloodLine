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
	static InputSystem &Instance();

	void Update();

	inline bool KeyPress(int keyEnum)
	{
		return IsKeyDown(keyEnum) == true && (keyUpdate[keyEnum] == updateCounter);
	}
	inline bool KeyRelease(int keyEnum)
	{
		return IsKeyDown(keyEnum) == false && (keyUpdate[keyEnum] == updateCounter);
	}
	inline bool IsKeyDown(int keyEnum)
	{
		return keyState[keyEnum];
	}

	inline bool MousePress(int button)
	{
		return mouseState[button] && (mouseUpdate[button] == updateCounter);
	}
	inline bool MouseRelease(int button)
	{
		return IsMouseDown(button) == false && (mouseUpdate[button] == updateCounter);
	}
	inline bool IsMouseDown(int button)
	{
		return mouseState[button];
	}

	inline int GetMouseX()
	{
		return mouseX;
	}

	inline int GetMouseY()
	{
		return mouseY;
	}

	inline int GetCurrentKey()
	{
		return currentKey;
	}

	inline bool QuitRequested()
	{
		return quitRequested;
	}

	InputSystem(const InputSystem &) = delete;
	InputSystem(InputSystem &&) = delete;
	void operator=(const InputSystem &) = delete;
	void operator=(InputSystem &&) = delete;

private:
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