#include "TitleState.h"

#include "Entity/GameObject.h"
#include "Components/Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Components/CameraFollower.h"
#include "Components/Text.h"

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
    if (InputManager::KeyPress(SDLK_ESCAPE) || InputManager::QuitRequested())
    {
        m_quitRequested = true;
    }
    if (InputManager::KeyPress(SDLK_SPACE))
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