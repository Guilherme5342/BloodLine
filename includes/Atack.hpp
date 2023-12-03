#pragma once

#include "Component.hpp"
#include "Sprite.hpp"

const float ATACK_DURATION = 0.2f;

class Atack : public Component
{
private:
    int damage;

public:
    Atack(GameObject &associated, float angle, int damage, string sprite, bool targetsPlayer, int direction, int frameCount = 1);
    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();
    int direction;

    float atackElapsedTime;
    bool canAtack = true;
    bool targetsPlayer;
};
