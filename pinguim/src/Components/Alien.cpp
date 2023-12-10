#include "Alien.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Minion.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"
#include "PeguinBody.h"

#include <limits>
#include <iostream>
#include <cmath>

std::int32_t Alien::m_alienCount = 0;

Alien::Alien(GameObject &associated, std::int32_t minionCount)
    : Component(associated)
{
    Sprite *sprite = new Sprite(associated, "res/img/alien.png");
    associated.AddComponent(sprite);

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    m_hp = 200;
    m_minionCount = minionCount;
    m_speed = {0, 0};
    m_state = AlienState::RESTING;
    m_waitTime = rand() % 3 + 1;

    Alien::m_alienCount++;
}

Alien::~Alien()
{
    Alien::m_alienCount--;
    m_minionArray.clear();
}

void Alien::Start()
{
    float angleOffset = 360 / m_minionCount;
    State &state = Game::GetCurrentState();
    for (size_t i = 0; i < m_minionCount; i++)
    {
        GameObject *minion = new GameObject();
        Minion *minionComponent = new Minion(*minion, state.GetObjectPtr(&m_associated), i * angleOffset);
        minion->AddComponent(minionComponent);
        m_minionArray.push_back(state.AddObject(minion));
    }
}

void Alien::Update(float deltaTime)
{
    float change = -10 * deltaTime;
    m_associated.m_angleDeg += change;
    m_associated.m_angleDeg -= (m_associated.m_angleDeg < 360) * 360;

    switch (m_state)
    {
    case AlienState::RESTING:
    {
        m_restTime.Update(deltaTime);
        if (m_restTime.Get() > m_waitTime)
        {
            m_waitTime = rand() % 5 + 1;
            m_restTime.Restart();
            if (PenguinBody::m_player)
            {
                m_destination = PenguinBody::m_player->GetPosition();
                float linearSpeed = 200 + (m_destination.Distance(m_associated.m_box.GetCenter()) / 1000) * (100);
                m_speed = (m_destination - m_associated.m_box.GetCenter()).Normalized() * linearSpeed * deltaTime;
            }
            m_state = AlienState::MOVING;
        }
        break;
    }
    case AlienState::MOVING:
    {
        if (m_associated.m_box.GetCenter().Distance(m_destination) <= 1)
        {
            if (PenguinBody::m_player)
            {
                m_associated.m_box.SetCenter(m_destination);
                Shoot(PenguinBody::m_player->GetPosition());
                m_state = AlienState::RESTING;
            }
        }
        else
        {
            m_associated.m_box.SetCenter(m_associated.m_box.GetCenter() + m_speed);
        }
        break;
    }
    default:
        break;
    }

    if (m_hp <= 0)
    {
        m_associated.RequestDelete();
    }
}

void Alien::NotifyCollision(GameObject &other)
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

        Sprite *sprite = new Sprite(*explosion, "res/img/aliendeath.png", 4, 0.3, false, 4 * 0.3);
        explosion->AddComponent(sprite);
        explosion->m_box.SetCenter(m_associated.m_box.GetCenter());

        Sound *sound = new Sound(*explosion, "res/audio/boom.wav");
        explosion->AddComponent(sound);
        sound->Play();

        Game::GetCurrentState().AddObject(explosion);
    }
    other.RequestDelete();
}

void Alien::Render() const
{
}

void Alien::Shoot(Vec2 playerPos) const
{
    std::shared_ptr<GameObject> minionGo = nullptr;
    float minDist = std::numeric_limits<float>::infinity();

    for (size_t i = 0; i < m_minionArray.size(); i++)
    {
        std::shared_ptr<GameObject> ptr = m_minionArray[i].lock();
        if (ptr == nullptr)
            continue;
        float dist = ptr->m_box.Distance(playerPos);
        if (dist < minDist)
        {
            minDist = dist;
            minionGo = ptr;
        }
    }

    if (minionGo != nullptr)
    {
        Minion *minionComp = static_cast<Minion *>(minionGo->GetComponent("Minion"));
        if (minionComp != nullptr)
        {
            minionComp->Shoot(playerPos);
        }
    }
}