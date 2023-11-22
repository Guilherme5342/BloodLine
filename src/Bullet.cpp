#include "Bullet.hpp"
#include "Collider.hpp"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, bool targetsPlayer, int frameCount) : Component(associated)
{
    Vector2 speedtmp = Vector2(speed, 0);
    associated.angleDeg = angle * 180 / 3.14;

    this->speed = speedtmp.GetRotated2(angle);
    this->targetsPlayer = targetsPlayer;
    distanceLeft = maxDistance;
    this->damage = damage;
    Sprite *spritetmp = new Sprite(associated, sprite, frameCount);

    associated.box.w = spritetmp->GetWidth();
    associated.box.h = spritetmp->GetHeight();
    associated.AddComponent(spritetmp);
    associated.AddComponent(new Collider(associated));
    associated.box.SetCenter(associated.box.GetCenter() + Vector2(125, 0).GetRotated(angle));

    cout << "Bullet created" << endl;
}

void Bullet::Update(float dt)
{
    Vector2 traveledDistance = Vector2(speed.x * dt, speed.y * dt);
    associated.box.SetCenter(associated.box.GetCenter() + traveledDistance);
    distanceLeft -= traveledDistance.GetMagnitude();
    if (distanceLeft <= 0)
    {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(string typeIdentifier)
{
    return typeIdentifier == "Bullet";
}

int Bullet::GetDamage()
{
    return damage;
}
