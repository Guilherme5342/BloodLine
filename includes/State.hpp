#pragma once

#include <memory>
#include <vector>

#include "InputSystem.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include "Resources.hpp"

class State
{

protected:
	std::vector<std::shared_ptr<GameObject>> objectArray;

	bool popRequested, quitRequested, started;

	virtual void StartArray();
	virtual void FixedUpdateArray(float fixedDt);
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	GameObject* AddStubGameObject(std::string name,Component* initialComp);

public:
	State();
	virtual ~State();

	virtual void LoadAssets() = 0;

	/// <summary>
	/// Pausa o Estado Atual após o empilhamento de um Estado Novo
	/// </summary>
	virtual void Pause() = 0;
	/// <summary>
	///
	/// </summary>
	virtual void Resume() = 0;
	virtual void Start() = 0;
	virtual void FixedUpdate(float fixedDt) {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual std::weak_ptr<GameObject> AddObject(GameObject *obj);
	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject *obj);

	bool PopRequested();
	bool QuitRequested();
};

inline std::weak_ptr<GameObject> State::AddObject(GameObject *obj)
{
	std::shared_ptr<GameObject> newObj(obj);

	objectArray.push_back(newObj);
	if (started)
	{
		newObj->Start();
	}

	return std::weak_ptr<GameObject>(newObj);
}

inline std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *obj)
{
	std::weak_ptr<GameObject> ptrToFind;

	for (int i = static_cast<int>(objectArray.size() - 1); i > 0; i--)
	{
		if (objectArray[i].get() == obj)
		{
			ptrToFind = objectArray[i];
		}
	}

	return ptrToFind;
}

inline bool State::PopRequested()
{
	return popRequested;
}

inline bool State::QuitRequested()
{
	return quitRequested;
}