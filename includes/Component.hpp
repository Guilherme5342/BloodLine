#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <type_traits>

class GameObject;

class Component
{

protected:
	GameObject &associated;

public:
	Component(GameObject &associated);
	virtual ~Component();

	virtual void Start()
	{
	}
	virtual void FixedUpdate(float fixedDt) {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool Is(std::string type) = 0;

	template <class T, class = std::is_base_of<Component, T>>
	std::string ResolveComponent()
	{
		return std::string(typeid(T).name());
	}
	virtual void NotifyCollision(GameObject &otherObj) {}
};