#include "GameObject.hpp"

GameObject::GameObject(string name, int layer) : name(name), layer(layer) // Member Initialization Lists
{
	dead = false;
	started = false;
	angleDeg = 0;
}

GameObject::GameObject(string name, Component *compArray, int layer) : GameObject(name, layer)
{
	AddComponent(compArray);
	
}

GameObject::~GameObject()
{
	for (int i = (int)components.size(); i > 0; i--)
	{
		components.erase(components.begin() + i);
	}

	components.clear();
}

void GameObject::Start()
{
	started = true;
	for (std::vector<std::unique_ptr<Component>>::iterator item = components.begin(); item != components.end(); item++)
	{
		item->get()->Start();
	}
}

void GameObject::Update(float dt)
{

	for (std::vector<std::unique_ptr<Component>>::iterator item = components.begin(); item != components.end(); item++)
	{
		item->get()->Update(dt);
	}
}

void GameObject::Render()
{

	for (std::vector<std::unique_ptr<Component>>::iterator item = components.begin(); item != components.end(); item++)
	{
		item->get()->Render();
	}
}

void GameObject::AddComponent(Component *comp)
{

	if (started)
	{
		comp->Start();
	}

	components.emplace_back(comp);
}

Component *GameObject::GetComponent(std::string type)
{

	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->Is(type))
		{
			return components[i].get();
		}
	}
	return nullptr;
}

void GameObject::NotifyCollision(GameObject &otherObj)
{
	for (auto &comp : components)
	{
		comp->NotifyCollision(otherObj);
	}
}
