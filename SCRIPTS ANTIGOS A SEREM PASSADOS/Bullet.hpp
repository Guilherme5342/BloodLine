#pragma once

#include "Component.hpp"
#include "Sprite.hpp"

class Bullet : public Component
{
private:
    Vector2 speed;
    float distanceLeft;
    int damage;

public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount = 1);
    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();

    bool targetsPlayer;
};
