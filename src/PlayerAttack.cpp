#include "PlayerAttack.hpp"
#include "Game.hpp"

PlayerAttack::PlayerAttack(GameObject& associated, std::weak_ptr<GameObject> externalAssociated, Vector2 pos, Vector2 dir)
    : AttackGeneric(associated,externalAssociated, pos, dir)
{
    attackCollider = new Collider(associated, { 175,175 },
        { 1,1 }, true, true);
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Start()
{
   

   
}

void PlayerAttack::Update(float dt)
{
    if (InputSystem::Instance().KeyPress(SDLK_z)) {
        PerformAttack();
    }
}

void PlayerAttack::Render()
{
}

bool PlayerAttack::Is(std::string type)
{
    return type == "PlayerAttack";
}

void PlayerAttack::PerformAttack()
{
    GameObject* gameObject = new GameObject("AttackPlayer", "PlayerAttack", 2);

    attackCollider->SetOffset(associated.box.GetCenter() + Vector2(40, associated.box.y));
    cout << "AttackPerformed" << endl;
    gameObject->AddComponent(attackCollider);

    Game::GetState().AddObject(gameObject);
}
