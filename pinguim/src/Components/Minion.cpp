#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"
#include "Sound.h"

constexpr float arcSpeed = 30;

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg)
    : Component(associated), m_alienCenter(alienCenter)
{
    m_arc = arcOffsetDeg;
    Sprite *sprite = new Sprite(associated, "res/img/minion.png");
    associated.AddComponent(sprite);

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    float random = ((rand() % 500) / 1000.f) + 1;
    sprite->SetScale(random);

    m_hp = 40;

    Update(0.f);
}

Minion::~Minion()
{
}

void Minion::Update(float deltaTime)
{
    std::shared_ptr<GameObject> centerPtr = m_alienCenter.lock();
    if (centerPtr == nullptr)
    {
        m_associated.RequestDelete();
        return;
    }
    Vec2 moveOffset = {200.f, 0.f};
    float change = arcSpeed * deltaTime;
    m_arc += change;
    m_arc -= (m_arc > 360) * 360;
    m_associated.m_angleDeg = m_arc;
    moveOffset.RotateDeg(m_arc);
    moveOffset += centerPtr->m_box.GetCenter();
    m_associated.m_box.SetCenter(moveOffset);

    if (m_hp <= 0)
    {
        m_associated.RequestDelete();
    }
}

void Minion::NotifyCollision(GameObject &other)
{
    Bullet *bullet = static_cast<Bullet *>(other.GetComponent("Bullet"));
    if (bullet == nullptr || bullet->m_targetsPlayer)
    {
        return;
    }
    m_hp -= bullet->GetDamage();
    if (m_hp <= 0)
    {
        GameObject *explosion = new GameObject();
        explosion->m_angleDeg = m_associated.m_angleDeg;

        Sprite *sprite = new Sprite(*explosion, "res/img/miniondeath.png", 4, 0.3, false, 4 * 0.3);
        explosion->AddComponent(sprite);
        explosion->m_box.SetCenter(m_associated.m_box.GetCenter());

        Sound *sound = new Sound(*explosion, "res/audio/boom.wav");
        explosion->AddComponent(sound);
        sound->Play();

        Game::GetCurrentState().AddObject(explosion);
    }
    other.RequestDelete();
}

void Minion::Render() const
{
}

void Minion::Shoot(Vec2 target)
{
    GameObject *go = new GameObject();
    const Vec2 &minionPos = m_associated.m_box.GetCenter();
    float angleDeg = minionPos.InclinationDeg(target);
    go->m_angleDeg = angleDeg;
    Bullet *projetil = new Bullet(*go, angleDeg, 700, true, "res/img/minionbullet2.png", 3, 0.1);
    go->m_box.SetCenter(minionPos);
    go->AddComponent(projetil);

    Game::GetCurrentState().AddObject(go);
}
