#include "Atack.hpp"
#include "Galapagos/Components/Collider.hpp"
#include "Components/HealthHandler.hpp"

Atack::Atack(GameObject &associated, float angle, int damage, std::string sprite, bool targetsPlayer, int direction, int frameCount) : Component(associated)
{
    associated.m_angleDeg = angle * 180 / 3.14;
    
    this->targetsPlayer = targetsPlayer;
    this->damage = damage;
    this->direction = direction;
    canAtack = false;
    atackElapsedTime = 0;

    associated.m_box.w = 20;
    associated.m_box.h = 100;
    Collider *collider = new Collider(associated);
    collider->isTrigger = true;
    associated.AddComponent(collider);

    if(direction == 0){
        direction = 1;
    }

    if(direction < 0){
        direction = -2;
    }

    associated.m_box.SetCenter(associated.m_box.GetCenter() + Vec2(20 * direction, -50).RotatedDeg(angle));
}

void Atack::Update(float dt)
{
    std::cout << direction << std::endl;
    if(!canAtack){
        atackElapsedTime += dt;
        if (atackElapsedTime >= ATACK_DURATION)
        {
            atackElapsedTime = 0;
            canAtack = true;
            m_associated.RequestDelete();
        }
    }
   
}

void Atack::Render() const {}

bool Atack::Is(std::string typeIdentifier) const
{
    return typeIdentifier == "Atack";
}

int Atack::GetDamage()
{
    return damage;
}

void Atack::NotifyCollision(GameObject &otherObj)
{
    HealthHandler* otherHealth = (HealthHandler*)otherObj.GetComponent("HealthHandler");
    if(otherObj.layer == 0 && otherHealth != nullptr && otherHealth->GetHealth() > 0 && !targetsPlayer){
        otherHealth->RemoveHealth(damage);
    }
}