#include "Atack.hpp"
#include "Collider.hpp"

Atack::Atack(GameObject &associated, float angle, int damage, std::string sprite, bool targetsPlayer, int direction, int frameCount) : Component(associated)
{
    associated.angleDeg = angle * 180 / 3.14;
    
    this->targetsPlayer = targetsPlayer;
    this->damage = damage;
    this->direction = direction;
    canAtack = false;
    atackElapsedTime = 0;

    associated.box.w = 20;
    associated.box.h = 100;
    Collider *collider = new Collider(associated);
    collider->SetTrigger(true);
    associated.AddComponent(collider);

    if(direction == 0){
        direction = 1;
    }

    if(direction < 0){
        direction = -2;
    }

    associated.box.SetCenter(associated.box.GetCenter() + Vector2(20 * direction, -50).GetRotated(angle));
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
            associated.RequestDelete();
        }
    }
   
}

void Atack::Render() {}

bool Atack::Is(std::string typeIdentifier)
{
    return typeIdentifier == "Atack";
}

int Atack::GetDamage()
{
    return damage;
}

void Atack::NotifyCollision(GameObject &otherObj)
{
    if(otherObj.layer == 0 && otherObj.healthHandler != nullptr && otherObj.healthHandler->GetHealth() > 0 && !targetsPlayer){
        otherObj.healthHandler->RemoveHealth(damage);
    }
}