#pragma once

#include "Vector3.h"
#include "Component.h"

class CameraFollower : public Component {

public:
	CameraFollower(GameObject& associated);
	// Herdado por meio de Component
	void Update(float dt);

	void Render();

	inline bool Is(std::string type) {
		return type == "CameraFollower";
	}

};
