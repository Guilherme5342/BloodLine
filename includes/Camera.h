#pragma once

#include "Vector3.h"
#include "GameObject.h"

class Camera {

private:
	static Vector2 pos, speed;

	static GameObject* focus;

public:
	inline static Vector2 GetCurrentCamPos() {
		return pos;
	}
	inline static void Follow(GameObject* newFocus) {
		focus = newFocus;
	}
	inline static void Unfollow() {
		focus = nullptr;
	}
	inline static void Reset() {
		pos = Vector2(0, 0);
	}
	static void Update(float dt);

};