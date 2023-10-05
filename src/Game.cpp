#include "Game.hpp"

Game *Game::instance = nullptr;

Game::Game(string windowName, int windowWidth, int windowHeight)
{
	int initiationFlag = SDL_Init(SDL_INIT_EVERYTHING);

	int imageInit = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG /* | IMG_INIT_TIF*/);

	int mixInit = Mix_Init(MIX_INIT_EVERYTHING);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_AllocateChannels(MIX_CHANNELS);

	int ttfInit = TTF_Init();
	cout << imageInit << endl;

	if (initiationFlag != 0 || imageInit == 0 || mixInit == 0 || ttfInit != 0)
	{
		std::cout << "Erro de Inicializao: " << SDL_GetError() << std::endl;
	}

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game()
{
	if (storedState != nullptr)
	{
		delete storedState;
	}

	Resources::ClearAll();

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_CloseAudio();

	IMG_Quit();

	SDL_Quit();
}

Game &Game::Instance()
{
	if (instance == nullptr)
		instance = new Game("EnginHoca");

	return *instance;
}

void Game::Run()
{
	if (storedState != nullptr)
	{
		stateStack.emplace(storedState);
		storedState = nullptr;
	}

	if (stateStack.empty())
	{
		return;
	}

	GetState().Start();
	// Atualiza��o da GAME ENGINE
	// Nunca esquecer de colocar as atualiza��es das Features que forem feitas na GameEngine
	// (Ex. InputSystem.Update(), Physics.Update(), Animator.Update())

	// Cria instancia de input fora do loop para não re-criar instancia a cada iteração
	InputSystem &input = InputSystem::Instance();

	// Checa quit requested do input, não do state (Mais otimizado), pois
	// não é necessário criar instância de InputSystem no UpdateState()
	while (!stateStack.empty() && !input.QuitRequested())
	{
		CalculateDeltaTime();
		input.Update();

		if (GetState().PopRequested())
		{
			stateStack.pop(); // Desempilha o Estado atual e Resume o Estado Anterior
			if (!stateStack.empty())
				GetState().Resume();
		}

		if (storedState != nullptr)
		{

			GetState().Pause();

			stateStack.emplace(storedState);
			GetState().Start();
			storedState = nullptr;
		}

		// Atualiza��o do Estado atual e seus componentes do Jogo
		if (!stateStack.empty())
		{

			GetState().Update(deltaTime);
			GetState().Render();

			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
		}
		SDL_Delay(32);
	}
}
