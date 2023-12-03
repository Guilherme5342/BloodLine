#pragma once

#include "Component.hpp"
#include "Sprite.hpp"

class Atack : public Component
{
private:
    int damage;

public:
    Atack(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount = 1);
    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();

    bool targetsPlayer;
};
