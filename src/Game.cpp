#include "Game.hpp"

Game *Game::instance = nullptr;

Game::Game(string windowName, int windowWidth, int windowHeight)
{
	storedState = nullptr;

	fixedDeltaTime = FIXED_DELTATIME;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw std::runtime_error(std::string("Erro ao carregar SDL. ") + std::string(SDL_GetError()));
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
	{
		throw std::runtime_error(std::string("Erro ao carregar SDL_IMG. ") + std::string(SDL_GetError()));
	}

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
	{
		throw std::runtime_error(std::string("Erro ao carregar SDL_MIX. ") + std::string(SDL_GetError()));
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
	{
		throw std::runtime_error(std::string("Erro ao executar Mix_OpenAudio. ") + std::string(SDL_GetError()));
	}

	Mix_AllocateChannels(32);

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Erro ao carregar SDL_Ttf. ") + std::string(SDL_GetError()));
	}

	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
	if (window == nullptr)
	{
		throw std::runtime_error("Erro ao criar janela.");
	}

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		throw std::runtime_error("Erro ao criar renderer.");
	}

	srand(time(NULL));
}

Game::~Game()
{
	if (storedState != nullptr)
	{
		delete storedState;
	}

	while (!stateStack.empty())
	{
		stateStack.pop();
	}

	Resources::ClearAll();

	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	cout << "Fechando Jogo" << endl;
}

Game &Game::Instance()
{
	if (instance == nullptr)
		instance = new Game("EnginHoca");

	return *instance;
}

void Game::__Run()
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
	// Atualização da GAME ENGINE
	// Nunca esquecer de colocar as atualizações das Features que forem feitas na GameEngine
	// (Ex. InputSystem.Update(), Physics.Update(), Animator.Update())

	// Cria instancia de input fora do loop para não re-criar instancia a cada iteração
	InputSystem &input = InputSystem::Instance();

	// Checa quit requested do input, não do state (Mais otimizado), pois
	// não é necessário criar instância de InputSystem no UpdateState()
	// CAIO -> Não esta saindo do jogo quando se pressiona ESC no Menu
	while (!stateStack.empty() && !GetState().QuitRequested() && !input.QuitRequested())
	{
		CalculateDeltaTime();
		input.Update();

		// Update de Física
		counter -= leftOver;
		while (counter <= deltaTime)
		{
			GetState().FixedUpdate(fixedDeltaTime);
			counter += fixedDeltaTime;
		}
		int x = deltaTime / fixedDeltaTime;
		leftOver = deltaTime - fixedDeltaTime * x;

		if (GetState().PopRequested())
		{
			stateStack.pop(); // Desempilha o Estado atual e Resume o Estado Anterior
			Resources::ClearRemaining();
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

void Game::CalculateDeltaTime()
{
	float currentTime = SDL_GetTicks64();			  // Pega o tempo atual
	deltaTime = (currentTime - frameStart) / 1000.0f; //
	frameStart = currentTime;

	leftOver = deltaTime - fixedDeltaTime;
}

GameObject *Game::__Instantiate(Component *component, Vector2 position)
{
	GameObject *gameObj = new GameObject();
	gameObj->AddComponent(component);
	gameObj->box.SetCenter(position);
	GetState().AddObject(gameObj);
	return gameObj;
}
