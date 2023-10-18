#pragma once

#include "Rect.hpp"
#include "Component.hpp"

class CircleCollider : public Component {

private:
	Vector2 position;
	float radius;

public:
	CircleCollider(GameObject& associated);
	~CircleCollider();

	void Update(float dt);
	void Render();
	inline bool Is(std::string type) {
		return type == "CircleCollider";
	}

	inline void SetRadius(float radius) {
		this->radius = radius;
	}

	Rect box;
};
