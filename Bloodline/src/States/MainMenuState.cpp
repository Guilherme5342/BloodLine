#include "MainMenuState.hpp"

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Components/CameraFollower.hpp"
#include "Galapagos/Components/Text.hpp"
#include "Galapagos/Utils/ParticlePresets.hpp"

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

    Sprite *background = new Sprite(*titleImage, "res/img/MainMenu.png", 40, 0.084f, true, 7, 6);
    titleImage->AddComponent(background);

    CameraFollower *cameraFollower = new CameraFollower(*titleImage);
    titleImage->AddComponent(cameraFollower);
    background->SetDist(0, 0, 1440 , 810);
    m_objectArray.emplace_back(titleImage);

    GameObject* buttonStartObject = new GameObject();
    Button* startButton = new Button(*buttonStartObject, [&]() {Game::Push(new StageState()); }, "Novo Jogo", "res/img/UI/Novo jogo.png");
    buttonStartObject->AddComponent(startButton);
    m_objectArray.emplace_back(buttonStartObject);
    buttonStartObject->m_box.SetCenter({ 720, 300 });

    //GameObject* buttonConfigObject = new GameObject();
    //Button* configButton = new Button(*buttonConfigObject, [&]() {Game::Push(new StageState()); }, "Config", "res/img/UI/botao.png");
    //buttonConfigObject->AddComponent(configButton);
    //m_objectArray.emplace_back(buttonConfigObject);
    //buttonConfigObject->m_box.y = 150;

    GameObject* leaveButtonObject = new GameObject();
    Button* leaveButton = new Button(*leaveButtonObject, [&]() {m_quitRequested = true; }, "Sair", "res/img/UI/Sair.png");
    leaveButtonObject->AddComponent(leaveButton);
    m_objectArray.emplace_back(leaveButtonObject);
    leaveButtonObject->m_box.SetCenter({ 720, 500 });

    GameObject* emmiterObject = new GameObject();
    ParticleEmmiter* partEmm = new ParticleEmmiter(*emmiterObject, 1000);
    emmiterObject->AddComponent(partEmm);

    m_emmiter = partEmm;
    m_particleConfig = ParticlePreset::Fire;
    //m_particleConfig.lifeTime = 5.f;
    //m_particleConfig.startColor = { 0, 150, 200, 100 };
    //m_particleConfig.startSize = 20;
    //m_particleConfig.sizeVariation = 10;
    //m_particleConfig.velocity = { 0, 50 };
    //m_particleConfig.velocityVariation = { 100, 100 };
    //m_particleConfig.rate = 0.02;
    m_objectArray.emplace_back(emmiterObject);
}

void MainMenuState::Update(float deltaTime)
{
    UpdateArray(deltaTime);
    if (InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }
    if (m_emmiter && InputManager::IsMouseDown(MouseButton::Left)) {

        m_particleConfig.position = InputManager::GetMousePos();
        m_emmiter->Emit(m_particleConfig);

    }
}

void MainMenuState::Render() const
{
    RenderArray();
}

void MainMenuState::Start()
{
    Camera::position = { 0, 0 };
    LoadAssets();
    StartArray();
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