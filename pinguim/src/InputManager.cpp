#include "InputManager.h"

constexpr std::int32_t keyOffsetThreshold = 1073741824;
constexpr std::int32_t keyOffset = 1073741697;

InputManager::InputManager()
{
    m_mouseState.fill(false);
    m_mouseUpdate.fill(0);

    m_keyState.fill(false);
    m_keyUpdate.fill(0);
}

InputManager::~InputManager()
{
}

void InputManager::__Update()
{
    m_quitRequested = false;

    SDL_GetMouseState(&m_mouseX, &m_mouseY);

    SDL_Event event;
    m_updateCounter++;
    std::uint32_t index;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.repeat)
                break;

            index = GetKeyIndex(event.key.keysym.sym);
            m_keyState[index] = true;
            m_keyUpdate[index] = m_updateCounter;
            break;
        case SDL_KEYUP:
            index = GetKeyIndex(event.key.keysym.sym);
            m_keyState[index] = false;
            m_keyUpdate[index] = m_updateCounter;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_mouseState[event.button.button] = true;
            m_mouseUpdate[event.button.button] = m_updateCounter;
            break;
        case SDL_MOUSEBUTTONUP:
            m_mouseState[event.button.button] = false;
            m_mouseUpdate[event.button.button] = m_updateCounter;
            break;
        case SDL_QUIT:
            m_quitRequested = true;
            break;
        default:
            break;
        }
    }
}

bool InputManager::__KeyPress(SDL_Keycode key) const
{
    std::uint32_t index = GetKeyIndex(key);
    return m_keyState[index] && (m_keyUpdate[index] == m_updateCounter);
}

bool InputManager::__KeyRelease(SDL_Keycode key) const
{
    std::uint32_t index = GetKeyIndex(key);
    return (!m_keyState[index]) && (m_keyUpdate[index] == m_updateCounter);
}

bool InputManager::__IsKeyDown(SDL_Keycode key) const
{
    return m_keyState[GetKeyIndex(key)];
}

bool InputManager::__MousePress(Uint8 button) const
{
    return m_mouseState[button] && (m_mouseUpdate[button] == m_updateCounter);
}

bool InputManager::__MouseRelease(Uint8 button) const
{
    return (!m_mouseState[button]) && (m_mouseUpdate[button] == m_updateCounter);
}

bool InputManager::__IsMouseDown(Uint8 button) const
{
    return m_mouseState[button];
}

std::int32_t InputManager::__GetMouseX() const
{
    return m_mouseX;
}

std::int32_t InputManager::__GetMouseY() const
{
    return m_mouseY;
}

Vec2 InputManager::__GetMousePos() const
{
    return Vec2(static_cast<float>(m_mouseX), static_cast<float>(m_mouseY));
}

bool InputManager::__QuitRequested() const
{
    return m_quitRequested;
}

InputManager &InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

std::int32_t InputManager::GetKeyIndex(SDL_Keycode key) const
{
    return key - ((key >= keyOffsetThreshold) * keyOffset);
}