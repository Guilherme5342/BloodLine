#pragma once

#include "Collision.hpp"
#include "Component.hpp"

class Collider : public Component
{

private:
	Vector2 scale, offset;

	bool isTrigger;

public:
	Collider(GameObject &associated, Vector2 scale = Vector2{1, 1}, Vector2 offset = Vector2{0, 0}, bool trigger = false);
	~Collider();

	inline void SetScale(Vector2 scale)
	{
		this->scale = scale;
		box.SetSize(scale);
	}

	inline void SetScale(float x, float y) {
		SetScale(Vector2(x, y));
	}

	inline void SetOffset(Vector2 offset)
	{
		this->offset = offset;
	}

	inline bool IsTrigger() {
		return this->isTrigger;
	}
	inline void SetTrigger(bool trigger) {
		isTrigger = trigger;
	}

	// Herdado por meio de Component
	virtual void Start();
	virtual void FixedUpdate(float fixedDt) override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	
	inline virtual bool Is(std::string type) override
	{
		return type == "Collider";
	}

	Rect box;
};