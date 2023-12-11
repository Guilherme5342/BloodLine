#include "TitleState.hpp"

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Components/CameraFollower.hpp"
#include "Galapagos/Components/Text.hpp"

#include "MainMenuState.hpp"

TitleState::TitleState()
{
}

TitleState::~TitleState()
{
    m_objectArray.clear();
}

void TitleState::LoadAssets()
{
    GameObject *titleImage = new GameObject();

    Sprite *background = new Sprite(*titleImage, "res/img/Title.png");
    titleImage->AddComponent(background);

    CameraFollower *cameraFollower = new CameraFollower(*titleImage);
    titleImage->AddComponent(cameraFollower);

    m_objectArray.emplace_back(titleImage);
}

void TitleState::Update(float deltaTime)
{
    UpdateArray(deltaTime);
    m_timer.Update(deltaTime);
    if (InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }
    if (InputManager::KeyPress(Key::Escape) || InputManager::KeyPress(Key::Space) ||
        InputManager::KeyPress(Key::Return) || InputManager::KeyPress(Key::Return2) || 
        InputManager::KeyPress(Key::Numpad_enter) || m_timer.Get() > 5)
    {
        m_popRequested = true;
        Game::Push(new MainMenuState());
    }
}

void TitleState::Render() const
{
    RenderArray();
}

void TitleState::Start()
{
    Camera::position = { 0, 0 };
    LoadAssets();
}

void TitleState::Pause()
{
}

void TitleState::Resume()
{
    Camera::position = { 0, 0 };
}