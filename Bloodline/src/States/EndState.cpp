#include "EndState.h"
#include "Galapagos/Core/GameObject.h"
#include "Galapagos/Components/Sprite.h"
#include "Galapagos/Core/InputManager.h"
#include "Galapagos/Core/Game.h"
#include "StageState.h"
#include "Galapagos/Components/CameraFollower.h"
#include "Galapagos/Components/Text.h"
#include "GameData.h"

EndState::EndState()
{
}

EndState::~EndState()
{
    m_music.Stop(0);
    m_objectArray.clear();
}

void EndState::LoadAssets()
{
    GameObject* endImage = new GameObject();

    std::string imgFile = "res/img/lose.jpg";
    std::string musicFile = "res/audio/endStateLose.ogg";

    if (GameData::playerVictory)
    {
        imgFile = "res/img/win.jpg";
        musicFile = "res/audio/endStateWin.ogg";
    }

    Sprite* background = new Sprite(*endImage, imgFile);
    endImage->AddComponent(background);

    CameraFollower* cameraFollower = new CameraFollower(*endImage);
    endImage->AddComponent(cameraFollower);

    m_objectArray.emplace_back(endImage);

    GameObject* textObject = new GameObject();
    Text* text = new Text(*textObject, "res/font/Call me maybe.ttf", 30, Text::Style::BLENDED, "Presione Espaco para Jogar novamente ou esc para sair.", SDL_Color{ 63, 72, 204, 255 });
    textObject->AddComponent(text);
    textObject->m_box.SetCenter({ 512, 300 });

    m_music.Open(musicFile);
    m_music.Play(-1);

    m_objectArray.emplace_back(textObject);
}

void EndState::Update(float deltaTime)
{
    UpdateArray(deltaTime);
    if (InputManager::KeyPress(Key::Escape) || InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }
    if (InputManager::KeyPress(Key::Space))
    {
        m_popRequested = true;
        Game::Push(new StageState());
    }
}

void EndState::Render() const
{
    RenderArray();
}

void EndState::Start()
{
    Camera::position = { 0, 0 };
    LoadAssets();
}

void EndState::Pause()
{
}

void EndState::Resume()
{
    Camera::position = { 0, 0 };
}
