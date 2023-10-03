#pragma once

#include "Rect.h"
#include "Component.h"
#include "Collider.h"



#include <vector>

class GameObject {

private:
	std::vector<std::unique_ptr<Component>> components;
	bool dead, started;
	string name;

public:
	int layer;

	GameObject(string name = "", int layer = 0);
	~GameObject();

	void Start();
	void Update(float dt);
	void Render();

	void AddComponent(Component* comp);
	Component* GetComponent(std::string type);

	template<typename T, typename = is_base_of<Component,T>>
	bool TryGetComponent(T* component)
	{
		for (auto& comp : components) 
		{
			string compName = typeid(T).name();
			compName.erase(compName.begin() + 0, compName.begin() + 6);

			cout << compName << endl;

			if (comp->Is(compName)) 
			{
				*component = (T*)comp.get();
				return true;
			}
		}

		return false;
	}

	void NotifyCollision(GameObject& otherObj);
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

	inline bool CompareLayer(GameObject& otherObj) {
		return otherObj.layer == this->layer;
	}
	

	float angleDeg;

	Rect box;
};