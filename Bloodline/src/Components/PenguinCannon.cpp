#include "PenguinCannon.hpp"

#include <cmath>

#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Bullet.hpp"
#include "Galapagos/Components/Collider.hpp"

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody) : Component(associated)
{
    Sprite *sprite = new Sprite(associated, "res/img/cubngun.png");
    associated.AddComponent(sprite);

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    m_pbody = penguinBody;
    m_angle = 0;
}

void PenguinCannon::Start()
{
}

void PenguinCannon::Update(float deltaTime)
{
    m_timer.Update(deltaTime);
    std::shared_ptr<GameObject> peguinBody = m_pbody.lock();
    if (peguinBody == nullptr)
    {
        m_associated.RequestDelete();
        return;
    }
    m_associated.m_box.SetCenter(peguinBody->m_box.GetCenter());
    float angle = m_associated.m_box.GetCenter().InclinationDeg(InputManager::GetWorldMousePos());
    m_associated.m_angleDeg = angle;

    if (InputManager::MousePress(LEFT_MOUSE_BUTTON))
    {
        Shoot();
    }
}

void PenguinCannon::NotifyCollision(GameObject &other)
{
}

void PenguinCannon::Render() const
{
}

void PenguinCannon::Shoot()
{
    if (m_timer.Get() < 0.01)
    {
        return;
    }
    m_timer.Restart();

    const float angleRad = m_associated.m_angleDeg * M_PI / 180;

    GameObject *go = new GameObject();
    Vec2 cannonPos = m_associated.m_box.GetCenter();

    go->m_angleDeg = m_associated.m_angleDeg;
    Bullet *projetil = new Bullet(*go, m_associated.m_angleDeg, 500, false, "res/img/penguinbullet.png", 4, 0.4, false);
    go->AddComponent(projetil);

    cannonPos.x += 60 * cos(angleRad);
    cannonPos.y += 60 * sin(angleRad);
    go->m_box.SetCenter(cannonPos);

    Game::GetCurrentState().AddObject(go);
}