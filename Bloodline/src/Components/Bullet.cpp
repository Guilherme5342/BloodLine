#include "Bullet.hpp"
#include "Galapagos/Components/AnimatedSprite.hpp"
#include "Galapagos/Components/Collider.hpp"

Bullet::Bullet(GameObject& associated, float angle, float maxDistance, bool targetsPlayer, std::string sprite, std::uint32_t frameCount, float frameTime, bool loop)
    : Component(associated)
{
    AnimatedSprite* bulletSprite = new AnimatedSprite(associated, sprite, frameCount, frameTime, loop, frameCount, 1);
    associated.AddComponent(bulletSprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    m_targetsPlayer = targetsPlayer;
    m_damage = 10;
    m_speed = { 1, 0 };
    m_speed.RotateDeg(angle);

    m_distanceLeft = maxDistance;
}

Bullet::Bullet(GameObject& associated, float angle, float maxDistance, bool targetsPlayer, std::string sprite, std::uint32_t frameCount, float frameTime, bool loop, std::uint32_t columnCount, std::uint32_t rowCount)
    : Component(associated)
{
    AnimatedSprite*bulletSprite = new AnimatedSprite(associated, sprite, frameCount, frameTime, loop, columnCount, rowCount);
    associated.AddComponent(bulletSprite);

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    m_targetsPlayer = targetsPlayer;
    m_damage = 10;
    m_speed = {1, 0};
    m_speed.RotateDeg(angle);

    m_distanceLeft = maxDistance;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
    constexpr float velocity = 360.f;
    Vec2 moveVector = m_speed * velocity * deltaTime;

    m_associated.m_box.x += moveVector.x;
    m_associated.m_box.y += moveVector.y;

    m_distanceLeft -= moveVector.Magnitude();

    if (m_distanceLeft <= 0)
    {
        m_associated.RequestDelete();
    }
}

void Bullet::NotifyCollision(GameObject &other)
{
}

void Bullet::Render() const
{
}

std::int32_t Bullet::GetDamage() const
{
    return m_damage;
}