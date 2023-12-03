#include "Atack.hpp"
#include "Collider.hpp"

Atack::Atack(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount) : Component(associated)
{
    associated.angleDeg = angle * 180 / 3.14;

    this->targetsPlayer = targetsPlayer;
    this->damage = damage;
    canAtack = false;
    atackElapsedTime = 0;

    associated.box.w = 20;
    associated.box.h = 100;
    associated.AddComponent(new Collider(associated));
    associated.box.SetCenter(associated.box.GetCenter() + Vector2(20, -50).GetRotated(angle));
}

void Atack::Update(float dt)
{
    if(!canAtack){
        atackElapsedTime += dt;
        if (atackElapsedTime >= ATACK_DURATION)
        {
            atackElapsedTime = 0;
            canAtack = true;
            associated.RequestDelete();
        }
    }
   
}

void Atack::Render() {}

bool Atack::Is(string typeIdentifier)
{
    return typeIdentifier == "Atack";
}

int Atack::GetDamage()
{
    return damage;
}
