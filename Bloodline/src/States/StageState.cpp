#include "StageState.h"

#include <math.h>
#include <memory>

#include "Galapagos/Components/Sound.h"
#include "Galapagos/Components/TileMap.h"
#include "Galapagos/Components/TileSet.h"
#include "Galapagos/Components/CameraFollower.h"
#include "Galapagos/Core/InputManager.h"
#include "Galapagos/Core/Camera.h"
#include "Components/Alien.h"
#include "Components/PenguinBody.h"
#include "Galapagos/Utils/Collision.h"
#include "Galapagos/Core/Game.h"
#include "EndState.h"
#include "GameData.h"

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

    GameObject *level = new GameObject();

    Sprite *background = new Sprite(*level, "res/img/ocean.jpg");
    level->AddComponent(background);
    TileSet *tileSet = new TileSet(64, 64, "res/img/tileset.png");
    TileMap *tileMap = new TileMap(*level, "res/map/tileMap.txt", tileSet);
    level->AddComponent(tileMap);
    CameraFollower *cameraFollower = new CameraFollower(*level);
    level->AddComponent(cameraFollower);

    m_objectArray.emplace_back(level);

    for (std::int32_t i = 0; i < 6; i++)
    {
        GameObject *alien = new GameObject();
        Alien *alienComponent = new Alien(*alien, (rand() % 9) + 4);
        alien->AddComponent(alienComponent);
        alien->m_box.SetCenter({ static_cast<float>(rand() % 1400 + 100), static_cast<float>(rand() % 1400 + 100 )});

        m_objectArray.emplace_back(alien);
    }

    GameObject *penguin = new GameObject();
    PenguinBody *penguinComponent = new PenguinBody(*penguin);
    penguin->AddComponent(penguinComponent);
    penguin->m_box.SetCenter({704, 640});
    Camera::Follow(penguin);

    m_objectArray.emplace_back(penguin);
}

void StageState::Start()
{
    LoadAssets();
    StartArray();
    m_music.Play(-1);
    m_started = true;
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
    }

    Camera::Update(deltaTime);

    UpdateArray(deltaTime);

    for (size_t i = 0; i < m_objectArray.size(); i++)
    {
        for (size_t j = i + 1; j < m_objectArray.size(); j++)
        {
            if (Collision::IsColliding(m_objectArray[i]->m_box, m_objectArray[j]->m_box, m_objectArray[i]->m_angleDeg, m_objectArray[j]->m_angleDeg))
            {
                m_objectArray[i]->NotifyCollision(*(m_objectArray[j]));
                m_objectArray[j]->NotifyCollision(*(m_objectArray[i]));
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

    if (Alien::m_alienCount <= 0)
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
    }
    if (PenguinBody::m_player == nullptr)
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
    }
}

void StageState::Render() const
{
    RenderArray();
}

void StageState::Resume()
{
    m_music.Play(-1);
}