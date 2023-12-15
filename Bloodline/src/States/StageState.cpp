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

#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>


const std::array<std::string, 4u> LayerStrings =
{
    std::string("terrain"),
    std::string("Collision"),
    std::string("prototype"),
};


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
    m_music.Open("res/audio/stageState.ogg");

    GameObject* level = new GameObject();

    AnimatedSprite* background = new AnimatedSprite(*level, "res/img/stageStateLuaBG.png");
    level->AddComponent(background);

    CameraFollower* cameraFollower = new CameraFollower(*level);
    level->AddComponent(cameraFollower);

    level->m_box.SetSize(Game::GetWindowSize());
    background->SetScale(Vec2(3, 3));
    AddObject(level);

    LoadTMX("res/map/mapa1.tmx");
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

    //Player* playerComponent = new Player(*player);
    //player->AddComponent(playerComponent);

    AnimatedSprite* playerSprite = new AnimatedSprite(*player, PLAYER_IDLE, 3, 2, .1f);
    player->AddComponent(playerSprite);

    //Collider* collider = new Collider(*player);
    //collider->SetScale({ 25,35 });
    //player->AddComponent(collider);

    Rigidbody2D* rigid = new Rigidbody2D(*player, 100, 100);
    player->AddComponent(rigid);

    PlayerController* pc = new PlayerController(*player,*playerSprite,*rigid, 300);
    player->AddComponent(pc);

    GameObject* healthDisplayObj = new GameObject("HealthDisplay");
    HealthDisplay* healthDisplay = new HealthDisplay(*healthDisplayObj, 100, *pc);
    healthDisplayObj->AddComponent(healthDisplay);

    AddObject(healthDisplayObj);

    player->m_box.SetCenter(Game::GetWindowCenter());
    Camera::Follow(player);
    AddObject(player);

    // Enemies 
    GameObject* enemyObj = new GameObject("Enemy1");
    //AnimatedSprite* enemySprite = new AnimatedSprite(*enemyObj, PAWN_ENEMY_IDLE, 10, 1, .3f);

    EnemyBase* enemyTest = new PawnEnemy(*enemyObj, GetObjectPtr(player), 10, 1, Action::IDLE, EnemyTypePhysics::GROUND, 4);

    enemyObj->AddComponent(enemyTest);

    enemyObj->m_box.SetCenter(player->m_box.GetCenter() + Vec2(20, 0));


    //enemyTest->GetHitBox().SetScale(Vec2(25, 50));

    AddObject(enemyObj);


    LoadEnemy(Vec2(0, 0), Vec2(25, 25), GetObjectPtr(player));
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
                //std::cout << "aaaaaaaaaasadfasdf\n";
            }
        }
    }
}

void StageState::LoadEnemy(Vec2 pos, Vec2 size, std::weak_ptr<GameObject> player)
{
    GameObject* enemyObj = new GameObject("Enemy1");
    //AnimatedSprite* enemySprite = new AnimatedSprite(*enemyObj, PAWN_ENEMY_IDLE, 10, 1, .3f);

    EnemyBase* enemyTest = new PawnEnemy(*enemyObj, player, 10, 1, Action::IDLE, EnemyTypePhysics::GROUND, 4);

    enemyObj->AddComponent(enemyTest);

    enemyObj->m_box.SetCenter(player.lock()->m_box.GetCenter() + Vec2(20, 0));


    //enemyTest->GetHitBox().SetScale(Vec2(25, 50));

    AddObject(enemyObj);
}

void StageState::LoadTMX(std::string file)
{
    tmx::Map map;
    if (map.load(file))
    {
        GameObject* go = new GameObject();
        TileSet* tileSet = new TileSet(16, 16, "res/map/TilesetPlaceholder.png");
        TileMap* tileMap = new TileMap(*go, tileSet, map);
        go->AddComponent(tileMap);
        AddObject(go);
        std::cout << "Loaded Map version: " << map.getVersion().upper << ", " << map.getVersion().lower << std::endl;
        if (map.isInfinite())
        {
            std::cout << "Map is infinite.\n";
        }
        else
        {
            std::cout << "Map Dimensions: " << map.getBounds() << std::endl;
        }

        const auto& layers = map.getLayers();
        std::cout << "Map has " << layers.size() << " layers" << std::endl;
        for (const auto& layer : layers)
        {
            std::cout << "Found Layer: " << layer->getName() << std::endl;
            std::cout << "Layer Type: " << LayerStrings[static_cast<std::int32_t>(layer->getType())] << std::endl;
            std::cout << "Layer Dimensions: " << layer->getSize() << std::endl;
            std::cout << "Layer Tint: " << layer->getTintColour() << std::endl;

            if (layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();
                std::cout << "Found " << objects.size() << " objects in layer" << std::endl;
                for (const auto& object : objects)
                {
                    std::cout << "Object " << object.getUID() << ", " << object.getName() << std::endl;
                    const auto& properties = object.getProperties();
                    std::cout << "Object has " << properties.size() << " properties" << std::endl;
                    for (const auto& prop : properties)
                    {
                        std::cout << "Found property: " << prop.getName() << std::endl;
                        std::cout << "Type: " << int(prop.getType()) << std::endl;
                    }
                    GameObject* chao = new GameObject();
                    chao->m_box = { object.getAABB().left, object.getAABB().top, object.getAABB().width, object.getAABB().height};
                    Collider* col = new Collider(*chao, true);
                    AddObject(chao);
                }
            }
        }
    }
    else
    {
        std::cout << "Failed loading map" << std::endl;
    }
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