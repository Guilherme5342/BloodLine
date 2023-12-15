#include "Galapagos/Core/Game.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <cstdlib>
#include <cstdint>
#include <ctime>

#include "Galapagos/Core/Resources.hpp"
#include "Galapagos/Core/InputManager.hpp"

Game *Game::m_instance = nullptr;

int Game::windowWidth = 0;
int Game::windowHeight = 0;

Game &Game::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Game("Enzo Crisostomo - 190086751", 1440, 810);
    }
    return *m_instance;
}

Game::Game(const char *title, std::int32_t width, std::int32_t height)
{
    if (m_instance == nullptr)
    {
        m_instance = this;
    }

    m_fixedDeltaTime = 0.006f;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
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

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (m_window == nullptr)
    {
        throw std::runtime_error("Erro ao criar janela.");
    }

    windowWidth = width;
    windowHeight = height;

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
    {
        throw std::runtime_error("Erro ao criar renderer.");
    }

    if (TTF_Init() != 0)
    {
        throw std::runtime_error(std::string("Erro ao carregar SDL_Ttf. ") + std::string(SDL_GetError()));
    }

    srand(time(NULL));

    m_storedState = nullptr;
}

Game::~Game()
{
    if (m_storedState)
    {
        delete m_storedState;
    }

    while (!m_stateStack.empty())
    {
        m_stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();

    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    std::cout << "Game destroyed successfully\n";
}

void Game::__Run()
{
    if (m_storedState) {
        m_stateStack.emplace(m_storedState);
        m_stateStack.top()->Start();
        m_storedState = nullptr;
    }
    if(m_stateStack.empty()) {
        throw std::runtime_error("Game iniciado sem estado inicial.");
    }

    while (!m_stateStack.empty() && m_stateStack.top()->QuitRequested() == false)
    {
        if (m_stateStack.top()->PopRequested())
        {
            m_stateStack.pop();
            if (!m_stateStack.empty())
            {
                m_stateStack.top()->Resume();
            }
        }
        if (m_storedState)
        {
            if (!m_stateStack.empty())
            {
                m_stateStack.top()->Pause();
            }
            m_stateStack.emplace(m_storedState);
            m_stateStack.top()->Start();
            m_storedState = nullptr;
        }
        CalculateDeltaTime();
        InputManager::Update();

        m_counter -= m_leftOver;
        while (m_counter <= m_deltaTime) 
        {
            m_stateStack.top()->FixedUpdate(m_fixedDeltaTime);
            m_counter += m_fixedDeltaTime;
        }
        int xPos = m_deltaTime / m_fixedDeltaTime;
        m_leftOver = m_deltaTime - m_fixedDeltaTime * xPos;

        m_stateStack.top()->Update(m_deltaTime);
        m_stateStack.top()->Render();
        SDL_RenderPresent(m_renderer);
        SDL_SetRenderDrawColor(Game::GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);
        SDL_Delay(2);
    }
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearImages();
}

SDL_Renderer *Game::__GetRenderer()
{
    return m_renderer;
}

void Game::CalculateDeltaTime()
{
    static bool firstFrame = true;
    std::uint32_t previousFrame = m_frameStart;
    m_frameStart = SDL_GetTicks();
    m_deltaTime = (!firstFrame) * (m_frameStart - previousFrame) / 1000.f;
    firstFrame = false;
    m_leftOver = m_deltaTime - m_fixedDeltaTime;
}

void Game::__Push(State *state)
{
    m_storedState = state;
}

float Game::__GetDeltaTime() const
{
    return m_deltaTime;
}

State &Game::__GetCurrentState()
{
    return *m_stateStack.top();
}