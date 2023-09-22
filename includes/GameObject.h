#pragma once

#include "Rect.h"
#include "Component.h"

#include <vector>

class GameObject {

private:
	std::vector<std::unique_ptr<Component>> components;
	bool dead, started;

	string name;

public:
	GameObject(string name = "");
	~GameObject();

	void Start();
	void Update(float dt);
	void Render();

	void AddComponent(Component* comp);
	Component* GetComponent(std::string type);

	/// <summary>
	/// Seta IsDead como True, 
	/// É normalmente usado no Update de GameObjects pra serem destruídos após o Request
	/// </summary>
	inline void RequestDelete() {
		dead = true;
	}

	inline bool isDead() {
		return dead;
	}

	inline string Name() {
		return name;
	}

	float angleDeg;

	Rect box;
};