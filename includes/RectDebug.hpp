#pragma once

#include "Component.hpp"
#include "Rect.hpp"
#include "GameObject.hpp"

class RectDebugger : public Component
{

private:
	SDL_Rect debugRect;
	Rect gameObjectBox;

	SDL_Color color;

public:
	RectDebugger(GameObject &associated, float x, float y, float h, float w, SDL_Color color = {255,255,255,255});
	~RectDebugger();
	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;
	inline bool Is(std::string type)
	{
		return type == "RectDebugger";
	}
};