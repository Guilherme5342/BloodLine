#include "BloodSpell.hpp"
#include "Components/Bullet.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Spell.hpp"
#include "Galapagos/Core/Game.hpp"

BloodSpell::BloodSpell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Spell(associated, damage, range, healthCost, playerController), associated(associated)
{
}

void BloodSpell::Activate()
{
    std::cout << "Shoot -------------" << std::endl;

    GameObject *bulletObject = new GameObject();
    bulletObject->m_box.SetCenter(associated.m_box.GetCenter());
    float angle = 0;
    float speed = 200;
    int damage = 20;
    float maxDistance = 200;
    std::string sprite = "../assets/img/bullet.png";
    bool targetsPlayer = false;
    int frameCount = 1;

    Bullet *bullet = new Bullet(*bulletObject, angle, speed, maxDistance, sprite, targetsPlayer, frameCount, false);
    bulletObject->AddComponent(bullet);
    Game::GetCurrentState().AddObject(bulletObject);
}
