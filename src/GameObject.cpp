#include "GameObject.hpp"

GameObject::GameObject(string name, int layer) : layer(layer) // Member Initialization Lists
{
	this->name = name;
	dead = false;
	started = false;
	this->label = "";
	angleDeg = 0;
}

GameObject::GameObject(string name, string tag, int layer) : GameObject(name,layer)
{
	SetTag(tag);
}

GameObject::GameObject(string name, Component *compArray, int layer) : GameObject(name, layer)
{
	AddComponent(compArray);
	
}

GameObject::~GameObject()
{
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

void GameObject::PhysicsUpdate(float fixedDt)
{
	for (std::vector<std::unique_ptr<Component>>::iterator item = components.begin(); item != components.end(); item++)
	{
		item->get()->FixedUpdate(fixedDt);
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

void GameObject::RemoveComponent(Component* compToRemove)
{
	bool foundItem = false;
	int index = (int)components.size() - 1;

	while (index >= 0 && !foundItem)
	{
		if (components[index].get() == compToRemove) 
		{
			foundItem = true;	
		}
		else 
		{
			index--;
		}
	}

	components.erase(components.begin() + index);
}

void GameObject::NotifyCollision(GameObject &otherObj)
{
	for (auto &comp : components)
	{
		comp->NotifyCollision(otherObj);
	}
}
