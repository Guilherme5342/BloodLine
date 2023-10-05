#pragma once

#include "Collision.hpp"
#include "Component.hpp"

class Collider : public Component
{

private:
	Vector2 scale, offset;

public:
	Collider(GameObject &associated, Vector2 scale = Vector2{1, 1}, Vector2 offset = Vector2{0, 0});
	~Collider();

	inline void SetScale(Vector2 scale)
	{
		this->scale = scale;
	}

	inline void SetOffset(Vector2 offset)
	{
		this->offset = offset;
	}

	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;

	inline virtual bool Is(std::string type) override
	{
		return type == "Collider";
	}

	Rect box;
};