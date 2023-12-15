#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Components/Sprite.hpp"

const float ATACK_DURATION = 0.2f;

class Atack : public Component
{
private:
    int damage;

public:
    Atack(GameObject &associated, float angle, int damage, std::string sprite, bool targetsPlayer, int direction, int frameCount = 1);
    void Update(float dt);
    void NotifyCollision(GameObject &otherObj);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    int direction;

    float atackElapsedTime;
    bool canAtack = true;
    bool targetsPlayer;
};
