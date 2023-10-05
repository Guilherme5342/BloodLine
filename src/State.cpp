#include "State.hpp"

State::State()
{
	quitRequested = false;
	started = false;
}

State::~State()
{
	objectArray.clear();
	cout << "Estado " << typeid(State).name() << "Deletado" << endl;
}

void State::StartArray()
{
	LoadAssets();

	for (auto obj : objectArray)
	{
		obj->Start();
	}
	started = true;
}

void State::UpdateArray(float dt)
{
	InputSystem &input = InputSystem::Instance();

	if (input.KeyPress(SDLK_ESCAPE) || input.QuitRequested())
	{
		quitRequested = true;
	}

	for (auto obj : objectArray)
	{
		obj->Update(dt);
	}

	for (int i = (int)objectArray.size() - 1; i >= 0; i--)
	{
		if (objectArray[i]->isDead())
		{
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::RenderArray()
{
	for (auto obj : objectArray)
	{
		obj->Render();
	}
}
