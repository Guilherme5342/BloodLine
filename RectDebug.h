#pragma once

#include "Rect.h"
#include "Component.h"


class RectDebugger : public Component {
	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual bool Is(std::string type) override;
};