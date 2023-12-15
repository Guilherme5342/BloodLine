#include "BloodBarrage.hpp"
#include "Galapagos/Core/Game.hpp"

const float PI = 3.1415;

BloodBarrage::BloodBarrage(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Spell(associated, damage, range, healthCost, playerController), m_associated(associated)
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

    Bullet *bullet1 = new Bullet(*bulletObject2, angle2, speed, maxDistance, sprite, targetsPlayer, frameCount,false);
    bulletObject1->m_box.SetCenter(m_associated.m_box.GetCenter());
    bulletObject1->AddComponent(bullet1);

    Bullet *bullet2 = new Bullet(*bulletObject3, angle3, speed, maxDistance, sprite, targetsPlayer, frameCount,false);
    bulletObject2->m_box.SetCenter(m_associated.m_box.GetCenter());
    bulletObject2->AddComponent(bullet2);

    Bullet *bullet3 = new Bullet(*bulletObject4, angle4, speed, maxDistance, sprite, targetsPlayer, frameCount,false);
    bulletObject3->m_box.SetCenter(m_associated.m_box.GetCenter());
    bulletObject3->AddComponent(bullet3);

    Bullet *bullet4 = new Bullet(*bulletObject5, angle5, speed, maxDistance, sprite, targetsPlayer, frameCount,false);
    bulletObject4->m_box.SetCenter(m_associated.m_box.GetCenter());
    bulletObject4->AddComponent(bullet4);

    Bullet *bullet5 = new Bullet(*bulletObject1, angle1, speed, maxDistance, sprite, targetsPlayer, frameCount,false);
    bulletObject5->m_box.SetCenter(m_associated.m_box.GetCenter());
    bulletObject5->AddComponent(bullet5);

    Game::GetCurrentState().AddObject(bulletObject1);
    Game::GetCurrentState().AddObject(bulletObject2);
    Game::GetCurrentState().AddObject(bulletObject3);
    Game::GetCurrentState().AddObject(bulletObject4);
    Game::GetCurrentState().AddObject(bulletObject5);
}
