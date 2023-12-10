#pragma once

#include "Rect.hpp"
#include "Component.hpp"
#include "Collider.hpp"
#include "HealthHandler.hpp"

#include <vector>
#include <array>

class HealthHandler;

class GameObject
{

private:
	std::vector<std::unique_ptr<Component>> components;
	bool dead, started;

	std::string name;

public:
	int layer;

	GameObject(std::string name = "", int layer = 0);
	/// <summary>
	/// 
	/// 
	/// </summary>
	/// <param name="name">Nome do Objeto</param>
	/// <param name="tag"> Tag do Objeto (Usado nos Colliders) </param>
	/// <param name="layer">Layer de Colisão do Objeto</param>
	GameObject(std::string name, std::string tag, int layer = 0);
	GameObject(std::string name , Component *compArray, int layer = 0);
	~GameObject();

	HealthHandler *healthHandler;

	void Start();
	void Update(float dt);
	void PhysicsUpdate(float fixedDt);

	void Render();

	void AddComponent(Component *comp);
	void AddComponents(std::vector<Component*> comps);

	Component *GetComponent(std::string type);
	void RemoveComponent(Component* comp);

	template <typename T, typename = std::is_base_of<Component, T>>
	bool TryGetComponent(T *component)
	{
		for (auto &comp : components)
		{
			std::string compName = typeid(T).name();
			compName.erase(compName.begin() + 0, compName.begin() + 6);

			std::cout << compName << std::endl;

			if (comp->Is(compName))
			{
				component = static_cast<T *>(comp.get());

				return true;
			}
		}

		return false;
	}

	void NotifyCollision(GameObject &otherObj);
	void NotifyNoCollision(GameObject &otherObj);
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

	inline std::string Name() const
	{
		return name;
	}

	inline bool CompareLayer(GameObject &otherObj)
	{
		return otherObj.layer == this->layer;
	}

	float angleDeg;

	Rect box;

	std::string tag;
};