#pragma once

#include <SDL2/SDL_image.h>
#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Math/Rect.hpp"
#include "Galapagos/Core/GameObject.hpp"

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
	virtual void Render() const override;
	inline virtual bool Is(std::string type) const override
	{
		return type == "RectDebugger";
	}
};