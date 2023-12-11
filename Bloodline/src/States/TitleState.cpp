#include "TitleState.hpp"

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/InputManager.hpp"
#include "Galapagos/Core/Game.hpp"
#include "StageState.hpp"
#include "Galapagos/Components/CameraFollower.hpp"
#include "Galapagos/Components/Text.hpp"

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

    Sprite *background = new Sprite(*titleImage, "res/img/title.jpg");
    titleImage->AddComponent(background);

    CameraFollower *cameraFollower = new CameraFollower(*titleImage);
    titleImage->AddComponent(cameraFollower);

    m_objectArray.emplace_back(titleImage);

    GameObject *textObject = new GameObject();
    Text *text = new Text(*textObject, "res/font/Call me maybe.ttf", 50, Text::Style::BLENDED, "Presione Espaco para iniciar!", SDL_Color{63, 72, 204, 255});
    textObject->AddComponent(text);
    textObject->m_box.SetCenter({512, 300});

    m_objectArray.emplace_back(textObject);
}

void TitleState::Update(float deltaTime)
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