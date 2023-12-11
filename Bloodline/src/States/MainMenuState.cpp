#include "MainMenuState.hpp"

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"
#include "StageState.hpp"
#include "Galapagos/Components/CameraFollower.hpp"
#include "Galapagos/Components/Text.hpp"

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
    m_objectArray.clear();
}

void MainMenuState::LoadAssets()
{
    GameObject *titleImage = new GameObject();

    Sprite *background = new Sprite(*titleImage, "res/img/MainMenuBg.png", 40, 0.2f, true, 7, 6);
    titleImage->AddComponent(background);

    CameraFollower *cameraFollower = new CameraFollower(*titleImage);
    titleImage->AddComponent(cameraFollower);

    m_objectArray.emplace_back(titleImage);
}

void MainMenuState::Update(float deltaTime)
{
    UpdateArray(deltaTime);
    if (InputManager::KeyPress(Key::Escape) || InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }
    if (InputManager::KeyPress(Key::Space))
    {
        Game::Push(new StageState());
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
}

void MainMenuState::Pause()
{
}

void MainMenuState::Resume()
{
    Camera::position = { 0, 0 };
}