#include "BloodSpell.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "Spell.hpp"
#include "Game.hpp"

BloodSpell::BloodSpell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Spell(associated, damage, range, healthCost, playerController), associated(associated)
{
}

void BloodSpell::Activate()
{
    std::cout << "Shoot -------------" << std::endl;

    GameObject *bulletObject = new GameObject();
    bulletObject->box.SetCenter(associated.box.GetCenter());
    float angle = 0;
    float speed = 200;
    int damage = 20;
    float maxDistance = 200;
    std::string sprite = "../assets/img/bullet.png";
    bool targetsPlayer = false;
    int frameCount = 1;

    Bullet *bullet = new Bullet(*bulletObject, angle, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject->AddComponent(bullet);
    Game::GetState().AddObject(bulletObject);
}
