#include "PenguinBody.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "PenguinCannon.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Components/Collider.hpp"
#include "Bullet.hpp"
#include "Galapagos/Components/Sound.hpp"

PenguinBody *PenguinBody::m_player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)
{
    PenguinBody::m_player = this;

    Sprite *sprite = new Sprite(associated, "res/img/penguin.png");
    associated.AddComponent(sprite);

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    m_speed = {0, 0};
    m_linearSpeed = 0;
    m_angle = 0;
    m_hp = 100;
}

PenguinBody::~PenguinBody()
{
    PenguinBody::m_player = nullptr;
}

void PenguinBody::Start()
{
    State &state = Game::GetCurrentState();

    GameObject *penguinCannon = new GameObject();
    PenguinCannon *penguinCannonComponent = new PenguinCannon(*penguinCannon, state.GetObjectPtr(&m_associated));
    penguinCannon->AddComponent(penguinCannonComponent);
    m_pcannon = state.AddObject(penguinCannon);
}

void PenguinBody::Update(float deltaTime)
{
    m_angle += (InputManager::IsKeyDown(Key::D) - InputManager::IsKeyDown(Key::A)) * m_angularVelocity * deltaTime;
    m_linearSpeed += (InputManager::IsKeyDown(Key::W) - InputManager::IsKeyDown(Key::S)) * m_linearVelocity;
    // desacelerar
    m_linearSpeed += ((m_linearSpeed < 0) * m_friction + (m_linearSpeed > 0) * -m_friction);
    m_linearSpeed = ((m_linearSpeed < -m_friction) || (m_linearSpeed > m_friction)) * m_linearSpeed;

    bool tooFast = m_linearSpeed > m_maxFowardSpeed;
    bool tooFastBack = m_linearSpeed < m_maxBackwardSpeed;
    bool notFast = !(tooFast || tooFastBack);

    m_linearSpeed = (notFast * m_linearSpeed) + (tooFast * m_maxFowardSpeed) + (tooFastBack * m_maxBackwardSpeed);

    m_speed = Vec2(m_linearSpeed * deltaTime, 0).RotatedDeg(m_angle);

    Vec2 newPos = m_associated.m_box.GetCenter() + m_speed;
    newPos.x = newPos.x < 0 ? 0 : newPos.x;
    newPos.x = newPos.x > 1408 ? 1408 : newPos.x;
    newPos.y = newPos.y < 0 ? 0 : newPos.y;
    newPos.y = newPos.y > 1280 ? 1280 : newPos.y;
    m_associated.m_box.SetCenter(newPos);
    m_associated.m_angleDeg = m_angle;

    if (m_hp <= 0)
    {
        std::shared_ptr<GameObject> cannon = m_pcannon.lock();
        if (cannon != nullptr)
        {
            cannon->RequestDelete();
        }
        m_associated.RequestDelete();
    }
}

void PenguinBody::NotifyCollision(GameObject &other)
{
    Bullet *bullet = static_cast<Bullet *>(other.GetComponent("Bullet"));
    if (bullet == nullptr || !bullet->m_targetsPlayer)
    {
        return;
    }
    m_hp -= bullet->GetDamage();
    if (m_hp <= 0)
    {
        Camera::Unfollow();
        GameObject *explosion = new GameObject();
        explosion->m_angleDeg = m_associated.m_angleDeg;

        Sprite *sprite = new Sprite(*explosion, "res/img/penguindeath.png", 5, 0.1, false, 5 * 0.1);
        explosion->AddComponent(sprite);
        explosion->m_box.SetCenter(m_associated.m_box.GetCenter());

        Sound *sound = new Sound(*explosion, "res/audio/boom.wav");
        explosion->AddComponent(sound);
        sound->Play();

        Game::GetCurrentState().AddObject(explosion);
    }
    other.RequestDelete();
}

void PenguinBody::Render() const
{
}