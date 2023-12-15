#include "StageState.hpp"

#include <cmath>
#include <memory>

#include "Galapagos/Components/Sound.hpp"
#include "Galapagos/Components/TileMap.hpp"
#include "Galapagos/Components/TileSet.hpp"
#include "Galapagos/Components/CameraFollower.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Camera.hpp"

#include "Galapagos/Components/RigidBody2D.hpp"
#include "Galapagos/Components/RectDebug.hpp"
#include "Galapagos/Components/StateMachine.hpp"
#include "Components/HealthDisplay.hpp"

#include "Components/PlayerController.hpp"
#include "Components/Enemy/PawnEnemy.hpp"

#include "Components/Alien.hpp"
#include "Components/PenguinBody.hpp"
#include "Galapagos/Utils/Collision.hpp"
#include "Galapagos/Core/Game.hpp"

#include "Components/Player.hpp"
#include "EndState.hpp"
#include "GameData.hpp"

StageState::StageState() : m_music()
{
    m_quitRequested = false;
    m_started = false;
}

StageState::~StageState()
{
    m_music.Stop(0);
    m_objectArray.clear();
}

void StageState::LoadAssets()
{
    //m_music.Open("res/audio/stageState.ogg");

    GameObject *level = new GameObject();

    AnimatedSprite*background = new AnimatedSprite(*level, "res/img/ocean.jpg");
    level->AddComponent(background);
    TileSet *tileSet = new TileSet(16, 16, "res/map/TilesetPlaceholder.png");
    TileMap *tileMap = new TileMap(*level, "res/map/testecolisao/mapa1_terrain.csv", tileSet);

    level->AddComponent(tileMap);
    CameraFollower *cameraFollower = new CameraFollower(*level);
    level->AddComponent(cameraFollower);

    AddObject(level);

    GameObject* chao = new GameObject();
    Collider* col = new Collider(*chao, true);
    chao->m_box = { 0, 0, 600, 40 };
    chao->m_box.SetCenter(Game::GetWindowCenter() + Vec2{ 0, 300 });


    AddObject(chao);
    /*for (std::int32_t i = 0; i < 6; i++)
    {
        GameObject *alien = new GameObject();
        Alien *alienComponent = new Alien(*alien, (rand() % 9) + 4);
        alien->AddComponent(alienComponent);
        alien->m_box.SetCenter({ static_cast<float>(rand() % 1400 + 100), static_cast<float>(rand() % 1400 + 100 )});

        m_objectArray.emplace_back(alien);
    }*/

    /*GameObject *penguin = new GameObject();
    PenguinBody *penguinComponent = new PenguinBody(*penguin);
    penguin->AddComponent(penguinComponent);
    penguin->m_box.SetCenter({704, 640});
    Camera::Follow(penguin);

    m_objectArray.emplace_back(penguin);*/

    GameObject* player = new GameObject("PlayerBody", 1);

    Player* playerComponent = new Player(*player);
    player->AddComponent(playerComponent);

    //AnimatedSprite* playerSprite = new AnimatedSprite(*player, PLAYER_IDLE, 3, 2, .1f);
    //player->AddComponent(playerSprite);

    //Collider* collider = new Collider(*player);
    //collider->SetScale({ 25,35 });
    //player->AddComponent(collider);

    //Rigidbody2D* rigid = new Rigidbody2D(*player, 100, 100);
    //player->AddComponent(rigid);

    //PlayerController* pc = new PlayerController(*player,*playerSprite,*rigid, 300);
    //player->AddComponent(pc);

    //GameObject* healthDisplayObj = new GameObject("HealthDisplay");
    //HealthDisplay* healthDisplay = new HealthDisplay(*healthDisplayObj, 100, *pc);
    //healthDisplayObj->AddComponent(healthDisplay);

    //AddObject(healthDisplayObj);

    player->m_box.SetCenter(Game::GetWindowCenter());
    Camera::Follow(player);
    AddObject(player);

    // Enemies 
    //GameObject* enemyObj = new GameObject("Enemy1");
    //AnimatedSprite* enemySprite = new AnimatedSprite(*enemyObj, PAWN_ENEMY_IDLE, 10, 1, .3f);

    //EnemyBase* enemyTest = new PawnEnemy(*enemyObj, GetObjectPtr(player), 10, 1, Action::IDLE, EnemyTypePhysics::GROUND, 4);

    //enemyObj->AddComponent(enemyTest);

    //enemyObj->m_box.SetCenter(player->m_box.GetCenter() + Vec2(20, 0));

    //enemyTest->GetHitBox().SetScale(Vec2(25, 50));

    //AddObject(enemyObj);

    AddSquare(Game::GetWindowCenter() + Vec2(100, 512), Vec2(1100, 150));
    AddSquare(Game::GetWindowCenter() + Vec2(0, 512), Vec2(450, 150));
}

void StageState::Start()
{
    LoadAssets();
    StartArray();
    m_music.Play(-1);
    m_started = true;
    Camera::Reset();
}

void StageState::FixedUpdate(float fixedDeltaTime) 
{
    FixedUpdateArray(fixedDeltaTime);
}

GameObject* StageState::AddSquare(Vec2 pos, Vec2 size, SDL_Color color)
{
    GameObject* rectObj = new GameObject("Ground", 1);
    RectDebugger* newGround = new RectDebugger(*rectObj, pos.x, pos.y, size.x, size.y, color);
    rectObj->AddComponent(newGround);
    rectObj->AddComponent(new Collider(*rectObj));
    AddObject(rectObj);
    return rectObj;
}

void StageState::Update(float deltaTime)
{
    if (InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }

    if (InputManager::KeyPress(Key::Escape))
    {
        m_popRequested = true;
        return;
    }

    Camera::Update(deltaTime);

    UpdateArray(deltaTime);


    for (size_t i = 0; i < m_objectArray.size(); i++)
    {
        for (size_t j = i + 1; j < m_objectArray.size(); j++)
        {
            Collider* a = (Collider*)m_objectArray[i]->GetComponent("Collider");
            Collider* b = (Collider*)m_objectArray[j]->GetComponent("Collider");
            if (!a || !b)
                continue;

            if (Collision::IsColliding(m_objectArray[i]->m_box, m_objectArray[j]->m_box, m_objectArray[i]->m_angleDeg, m_objectArray[j]->m_angleDeg))
            {
                m_objectArray[i]->NotifyCollision(*(m_objectArray[j]));
                m_objectArray[j]->NotifyCollision(*(m_objectArray[i]));
                std::cout << "aaaaaaaaaasadfasdf\n";
            }
        }
    }

    for (size_t i = 0; i < m_objectArray.size(); i++)
    {
        if (m_objectArray.at(i)->IsDead())
        {
            m_objectArray.erase(m_objectArray.begin() + i);
        }
    }

    /*if (Alien::m_alienCount <= 0)
    {
        m_music.Stop(3000);
        m_timer.Update(deltaTime);
        if (m_timer.Get() > 3)
        {
            m_timer.Restart();
            m_popRequested = true;
            GameData::playerVictory = true;
            Game::Push(new EndState());
        }
    }*/
   /* if (PenguinBody::m_player == nullptr)
    {
        m_music.Stop(3000);
        m_timer.Update(deltaTime);
        if (m_timer.Get() > 3)
        {
            m_timer.Restart();
            m_popRequested = true;
            GameData::playerVictory = false;
            Game::Push(new EndState());
        }
    }*/
}

void StageState::Render() const
{
    RenderArray();
}

void StageState::Resume()
{
    m_music.Play(-1);
}