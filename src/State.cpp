#include "State.hpp"

State::State()
{
	popRequested = false;
	quitRequested = false;
	started = false;
}

State::~State()
{
	for (int i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->RequestDelete();
	}
	objectArray.clear();

	cout << "Estado " << typeid(State).name() << "Deletado" << endl;
}

GameObject *State::AddStubGameObject(string Name, Component *initialComp)
{
	GameObject *stubObj = new GameObject("[Stub] " + Name);
	stubObj->AddComponent(initialComp);
	return stubObj;
}

void State::StartArray()
{
	LoadAssets();

	for (int i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->Start();
	}
	started = true;
}

void State::FixedUpdateArray(float fixedDt)
{
	for (unsigned i = 0; i < objectArray.size(); i++)
	{
		Collider *currentCol = (Collider *)objectArray[i]->GetComponent("Collider");

		if (currentCol == nullptr)
			continue;

		for (unsigned j = i + 1; j < objectArray.size(); j++)
		{
			Collider *otherCol = (Collider *)objectArray[j]->GetComponent("Collider");
			if (otherCol == nullptr)
				continue;

			if (Collision::IsColliding(currentCol->box, otherCol->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg))
			{
				objectArray[i]->NotifyCollision(*objectArray[j]);
				objectArray[j]->NotifyCollision(*objectArray[i]);
			}
		}
	}

	for (int i = 0; i < (int)objectArray.size(); i++)
	{
		objectArray[i]->PhysicsUpdate(fixedDt);
	}
}

void State::UpdateArray(float dt)
{
	for (int i = 0; i < (int)objectArray.size(); i++)
	{
		objectArray[i]->Update(dt);
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
	for (int i = 0; i < static_cast<int>(objectArray.size()); i++) {
		objectArray[i]->Render();
	}
}
