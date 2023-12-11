#include "MainMenuState.hpp"

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Components/CameraFollower.hpp"
#include "Galapagos/Components/Text.hpp"

#include "StageState.hpp"
#include "Components/UI/Button.h"

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
    m_music.Stop(300);
    m_objectArray.clear();
}

void MainMenuState::LoadAssets()
{
    m_music.Open("res/audio/mainMenu.mp3");

    GameObject *titleImage = new GameObject();

    Sprite *background = new Sprite(*titleImage, "res/img/MainMenuBg.png", 40, 0.2f, true, 7, 6);
    titleImage->AddComponent(background);

    CameraFollower *cameraFollower = new CameraFollower(*titleImage);
    titleImage->AddComponent(cameraFollower);
    background->SetDist(0, 0, 1440 , 810);
    m_objectArray.emplace_back(titleImage);


    GameObject* buttonStartObject = new GameObject();
    Button* startButton = new Button(*buttonStartObject, [&]() {Game::Push(new StageState()); }, "Novo Jogo", "res/img/UI/botao.png");
    buttonStartObject->AddComponent(startButton);
    m_objectArray.emplace_back(buttonStartObject);
    buttonStartObject->m_box.y = 100;

    GameObject* buttonConfigObject = new GameObject();
    Button* configButton = new Button(*buttonConfigObject, [&]() {Game::Push(new StageState()); }, "Config", "res/img/UI/botao.png");
    buttonConfigObject->AddComponent(configButton);
    m_objectArray.emplace_back(buttonConfigObject);
    buttonConfigObject->m_box.y = 150;

    GameObject* leaveButtonObject = new GameObject();
    Button* leaveButton = new Button(*leaveButtonObject, [&]() {m_quitRequested = true; }, "Sair", "res/img/UI/botao.png");
    leaveButtonObject->AddComponent(leaveButton);
    m_objectArray.emplace_back(leaveButtonObject);
    leaveButtonObject->m_box.y = 200;
}

void MainMenuState::Update(float deltaTime)
{
    UpdateArray(deltaTime);
    if (InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }
}

void MainMenuState::Render() const
{
    RenderArray();
}

void MainMenuState::Start()
{
    Camera::position = { 0, 0 };
    StartArray();
    LoadAssets();
    m_music.Play(-1);
}

void MainMenuState::Pause()
{
    m_music.Stop(0);
}

void MainMenuState::Resume()
{
    Camera::position = { 0, 0 };
    m_music.Play(-1);
}