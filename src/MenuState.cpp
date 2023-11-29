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
	Sprite *titleCard = new Sprite(*titleObj, TITLE_IMAGE, 40, 1, .3f);

	titleObj->AddComponent(titleCard);

	GameObject *textObj = new GameObject("Title Text");
	textObj->AddComponent(new Text(*textObj, FONT, 75, TextStyle::SOLID,
								   "Bloodline", SDL_Color{255, 0, 0, 255}));

	// cout << Game::Instance().GetWindowCenter() << endl;
	textObj->box.SetCenter(Game::Instance().GetWindowCenter());

	Vector3 divd = Vector3(2, 2, 2);

	divd = divd / 2;

	Vector3 divd2 = Vector2(2.f, 312) * 10;

	cout << textObj->box.GetCenter() << endl;
	cout << divd << endl;

	objectArray.emplace_back(titleObj);
	objectArray.emplace_back(textObj);
}

void MenuState::Start()
{
	StartArray();
}

void MenuState::Update(float dt)
{
	InputSystem &input = InputSystem::Instance();

	if (input.KeyPress(SDLK_ESCAPE) || input.QuitRequested())
	{
		quitRequested = true;
	}
	if (input.KeyPress(SDLK_SPACE))
	{
		Game::Instance().PushState(new StageState());
	}

	// UpdateArray(dt);
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
