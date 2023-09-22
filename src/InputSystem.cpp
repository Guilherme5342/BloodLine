#include "InputSystem.h"

InputSystem::InputSystem() {
	quitRequested = false;
	updateCounter = 0;
}

InputSystem::~InputSystem()
{
}

InputSystem& InputSystem::Instance() {
	static InputSystem instance;
	return instance;
}

void InputSystem::Update() {
	SDL_Event event;

	SDL_GetMouseState(&mouseX, &mouseY);

	updateCounter++;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
				break;

			case SDL_MOUSEBUTTONUP:
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
				break;

			case SDL_KEYDOWN:
				if (event.key.repeat != 0) { return; }

				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;

				break;

			case SDL_KEYUP:
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
				break;

			case SDL_QUIT:
				quitRequested = true;
				break;
		}
	}
}