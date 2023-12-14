#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include <stack>
#include <memory>

#include "State.hpp"

class Game
{
public:
    ~Game();

    inline static void Run() { return GetInstance().__Run(); }
    inline static SDL_Renderer *GetRenderer() { return GetInstance().__GetRenderer(); }
    inline static State &GetCurrentState() { return GetInstance().__GetCurrentState(); }
    inline static float GetDeltaTime() { return GetInstance().__GetDeltaTime(); }

    inline static void Push(State* state) { return GetInstance().__Push(state); }

    Game(const Game &) = delete;
    Game(Game &&) = delete;
    void operator=(const Game &) = delete;
    void operator=(Game &&) = delete;

private:
    Game(const char *title, std::int32_t width, std::int32_t height);

    void __Run();
    void __Push(State* state);
    SDL_Renderer *__GetRenderer();
    State &__GetCurrentState();
    float __GetDeltaTime() const;

    static Game &GetInstance();

    void CalculateDeltaTime();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    State *m_storedState = nullptr;

    std::stack<std::unique_ptr<State>> m_stateStack;

    std::uint32_t m_frameStart;
    float m_deltaTime;
    float m_fixedDeltaTime;

    float m_leftOver = 0;
    float m_counter = 0;

    static Game *m_instance;
};
