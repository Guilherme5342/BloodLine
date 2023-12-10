#include "BloodBarrage.hpp"
#include "Game.hpp"

const float PI = 3.1415;

BloodBarrage::BloodBarrage(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Spell(associated, damage, range, healthCost, playerController), associated(associated)
{
}

void  BloodBarrage::Activate()
{
    std::cout << "Barrage -------------" << std::endl;

    GameObject *bulletObject1 = new GameObject();
    GameObject *bulletObject2 = new GameObject();
    GameObject *bulletObject3 = new GameObject();
    GameObject *bulletObject4 = new GameObject();
    GameObject *bulletObject5 = new GameObject();

    float angle1 = 0;
    float angle2 = PI/4;
    float angle3 = PI/2;
    float angle4 = PI * 3 / 2;
    float angle5 = PI;
    float speed = 200;
    int damage = 20;
    float maxDistance = 100;
    std::string sprite = "../assets/img/bullet.png";
    bool targetsPlayer = false;
    int frameCount = 1;

    Bullet *bullet1 = new Bullet(*bulletObject2, angle2, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject1->box.SetCenter(associated.box.GetCenter());
    bulletObject1->AddComponent(bullet1);

    Bullet *bullet2 = new Bullet(*bulletObject3, angle3, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject2->box.SetCenter(associated.box.GetCenter());
    bulletObject2->AddComponent(bullet2);

    Bullet *bullet3 = new Bullet(*bulletObject4, angle4, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject3->box.SetCenter(associated.box.GetCenter());
    bulletObject3->AddComponent(bullet3);

    Bullet *bullet4 = new Bullet(*bulletObject5, angle5, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject4->box.SetCenter(associated.box.GetCenter());
    bulletObject4->AddComponent(bullet4);

    Bullet *bullet5 = new Bullet(*bulletObject1, angle1, speed, damage, maxDistance, sprite, targetsPlayer, frameCount);
    bulletObject5->box.SetCenter(associated.box.GetCenter());
    bulletObject5->AddComponent(bullet5);

    Game::GetState().AddObject(bulletObject1);
    Game::GetState().AddObject(bulletObject2);
    Game::GetState().AddObject(bulletObject3);
    Game::GetState().AddObject(bulletObject4);
    Game::GetState().AddObject(bulletObject5);
}
