#include "Player.hpp"

#include "Galapagos/Components/AnimatedSprite.hpp"
#include "Galapagos/Core/InputManager.hpp"

static constexpr const char* playerRun = "res/img/player/run.png";

Player::Player(GameObject& associated) : Component(associated)
{
    AnimatedSprite* sprite = new AnimatedSprite(associated, playerRun, 8, 80.f/1000.f);
    associated.AddComponent(sprite);

    m_playerBody = new Rigidbody2D(associated);
    associated.AddComponent(m_playerBody);
}

void Player::NotifyCollision(GameObject& otherObj)
{
    m_associated.m_box.y -= 0.1;
    std::cout << "sadfasdf\n";
}

void Player::Update(float deltaTime)
{
    HandleInput(deltaTime);
}

void Player::Render() const
{
}

void Player::HandleInput(float deltaTime)
{
    m_playerBody->ApplyForce({ static_cast<float>(InputManager::IsKeyDown(Key::D) - InputManager::IsKeyDown(Key::A)) * 100, 0 });
    m_associated.m_box.x += InputManager::IsKeyDown(Key::D) - InputManager::IsKeyDown(Key::A);
    m_associated.m_box.y += 0.1;
}
