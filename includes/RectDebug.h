#pragma once

#include "Component.h"
#include "Rect.h"
#include "GameObject.h"

class RectDebugger : public Component {

private:
	SDL_Rect debugRect;
	Rect gameObjectBox;

public:
	RectDebugger(GameObject& associated, float x, float y, float h,float w);
	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;
	inline bool Is(std::string type) {
		return type == "RectDebugger";
	}
};