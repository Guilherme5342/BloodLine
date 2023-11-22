#include "BloodSpell.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "Spell.hpp"
#include "Game.hpp"

BloodSpell::BloodSpell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Spell(associated, damage, range, healthCost, playerController)
{
}

void BloodSpell::Activate()
{
    cout << "Shoot -------------" << endl;

    GameObject *bulletObject = new GameObject();
    float angle = 90;
    float speed = 200;
    int damage = 20;
    float maxDistance = 100;
    string sprite = "../assets/img/bullet.png";
    bool targetsPlayer = false;
    int frameCount = 1;

    Bullet *bullet = new Bullet(*bulletObject, angle, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject->AddComponent(bullet);
    Game::Instance().GetState().AddObject(bulletObject);
}
