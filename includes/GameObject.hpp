#pragma once

#include "Rect.hpp"
#include "Component.hpp"
#include "Collider.hpp"

#include <vector>
#include <array>

class GameObject
{

private:
	std::vector<std::unique_ptr<Component>> components;
	bool dead, started;
	std::string name;

public:
	int layer;

	GameObject(string name = "", int layer = 0);
	GameObject(string name , Component *compArray, int layer = 0);
	~GameObject();

	void Start();
	void Update(float dt);
	void PhysicsUpdate(float fixedDt);

	void Render();

	void AddComponent(Component *comp);
	Component *GetComponent(std::string type);

	template <typename T, typename = is_base_of<Component, T>>
	bool TryGetComponent(T *component)
	{
		for (auto &comp : components)
		{
			string compName = typeid(T).name();
			compName.erase(compName.begin() + 0, compName.begin() + 6);

			cout << compName << endl;

			if (comp->Is(compName))
			{
				component = static_cast<T *>(comp.get());

				return true;
			}
		}

		return false;
	}

	void NotifyCollision(GameObject &otherObj);
	/// <summary>
	/// Seta IsDead como True,
	/// � normalmente usado no Update de GameObjects pra serem destru�dos ap�s o Request
	/// </summary>
	inline void RequestDelete()
	{
		dead = true;
	}

	inline bool isDead()
	{
		return dead;
	}

	inline string Name() const
	{
		return name;
	}

	inline bool CompareLayer(GameObject &otherObj)
	{
		return otherObj.layer == this->layer;
	}

	float angleDeg;

	Rect box;
};