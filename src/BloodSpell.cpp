#include "BloodSpell.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "Spell.hpp"

BloodSpell::BloodSpell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Spell(associated, damage, range, healthCost, playerController)
{
}

void BloodSpell::Activate()
{
    GameObject *bulletObject = new GameObject();
    float angle = 90;
    float speed = 20;
    int damage = 20;
    float maxDistance = 300;
    string sprite = "src/bullet.png";
    bool targetsPlayer = false;
    int frameCount = 1;

    Bullet *bullet = new Bullet(*bulletObject, angle, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject->AddComponent(bullet);
    // Add bulletObject to the game world
}
