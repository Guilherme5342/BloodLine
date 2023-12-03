#include "Atack.hpp"
#include "Collider.hpp"

Atack::Atack(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount) : Component(associated)
{
    associated.angleDeg = angle * 180 / 3.14;

    this->targetsPlayer = targetsPlayer;
    this->damage = damage;

    associated.box.w = 100;
    associated.box.h = 100;
    associated.AddComponent(new Collider(associated));
    associated.box.SetCenter(associated.box.GetCenter() + Vector2(125, 0).GetRotated(angle));
}

void Atack::Update(float dt)
{

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
