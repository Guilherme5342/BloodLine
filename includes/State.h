#pragma once

#include <memory>
#include <vector>

#include "InputSystem.h"
#include "GameObject.h"
#include "Camera.h"
#include "CameraFollower.h"


class State
{

protected:
	std::vector<std::shared_ptr<GameObject>> objectArray;

	bool popRequested, quitRequested, started;

	virtual void StartArray();
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

public:
	State();
	virtual ~State();

	virtual void LoadAssets() = 0;

	/// <summary>
	/// Pausa o Estado Atual ap�s o empilhamento de um Estado Novp
	/// </summary>
	virtual void Pause() = 0;
	/// <summary>
	///
	/// </summary>
	virtual void Resume() = 0;
	virtual void Start() = 0;

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

	for (int i = 0; i < objectArray.size(); i++)
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