#include "MenuState.hpp"
#include "Game.hpp"

#ifdef _WIN32
#define FONT "assets/font/Call me maybe.ttf"
#else
#define FONT "../assets/font/Call me maybe.ttf"
#endif

MenuState::MenuState() : State()
{
}

MenuState::~MenuState()
{
	objectArray.clear();
}

void MenuState::LoadAssets()
{
	GameObject *titleObj = new GameObject("Title State");
	Sprite *titleCard = new Sprite(*titleObj, TITLE_IMAGE, 7, 6, .6f);
	titleCard->SetScale(Vector2(2.2f, 2.2f));
	titleCard->SetFrameSpan(0, 40);
	titleCard->SetLoop(true);
	titleObj->AddComponent(titleCard);

	GameObject *textObj = new GameObject("Title Text");
	textObj->AddComponent(new Text(*textObj, FONT, 75, TextStyle::SOLID,
								   "Bloodline", SDL_Color{255, 0, 0, 255})); 

	// cout << Game::GetWindowCenter() << endl;
	textObj->box.SetCenter(Game::GetWindowCenter());

	Vector3 divd = Vector3(2, 2, 2);

	divd = divd / 2;

	Vector3 divd2 = Vector2(2.f, 312) * 10;

	// cout << textObj->box.GetCenter() << endl;
	std::cout << divd << std::endl;

	objectArray.emplace_back(titleObj);
	// objectArray.emplace_back(textObj);
}

void MenuState::Start()
{
	StartArray();
}

void MenuState::Update(float dt)
{
	if (InputSystem::KeyPress(SDLK_ESCAPE) || InputSystem::QuitRequested())
	{
		quitRequested = true;
	}
	if (InputSystem::KeyPress(SDLK_SPACE))
	{
		Game::PushState(new StageState());
	}

	UpdateArray(dt);
}

void MenuState::Render()
{
	RenderArray();
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{

	Camera::Reset();
	StartArray();
	RenderArray();
}
