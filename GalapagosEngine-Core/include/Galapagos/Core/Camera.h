#pragma once
#include "Galapagos/Math/Vec2.h"

class GameObject;

class Camera
{
public:
    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float deltaTime);

    static Vec2 position;
    static Vec2 speed;

private:
    static GameObject *m_focus;
};