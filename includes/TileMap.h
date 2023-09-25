#pragma once

#include "Component.h"
#include "GameObject.h"

class TileMap : public Component {
	// Herdado por meio de Component
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual bool Is(std::string type) override;
};