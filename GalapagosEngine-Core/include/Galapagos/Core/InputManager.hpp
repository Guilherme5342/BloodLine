#pragma once

#include <array>
#include <cstdint>
#include <SDL2/SDL.h>

#include "Galapagos/Math/Vec2.hpp"
#include "Camera.hpp"
#include "KeyCodes.hpp"

class InputManager
{
public:
    static inline void Update() { return GetInstance().__Update(); }

    static inline bool QuitRequested() { return GetInstance().__QuitRequested(); }

    static inline bool KeyPress(Key key) { return GetInstance().__KeyPress(key); }
    static inline bool KeyRelease(Key key) { return GetInstance().__KeyRelease(key); }
    static inline bool IsKeyDown(Key key) { return GetInstance().__IsKeyDown(key); }

    static inline bool MousePress(MouseButton button) { return GetInstance().__MousePress(button); }
    static inline bool MouseRelease(MouseButton button) { return GetInstance().__MouseRelease(button); }
    static inline bool IsMouseDown(MouseButton button) { return GetInstance().__IsMouseDown(button); }

    static inline std::int32_t GetMouseX() { return GetInstance().__GetMouseX(); }
    static inline std::int32_t GetMouseY() { return GetInstance().__GetMouseY(); }
    static inline Vec2 GetMousePos() { return GetInstance().__GetMousePos(); }

    static inline std::int32_t GetWorldMouseX() { return GetInstance().__GetMouseX() + static_cast<std::int32_t>(Camera::position.x); }
    static inline std::int32_t GetWorldMouseY() { return GetInstance().__GetMouseY() + static_cast<std::int32_t>(Camera::position.y); }
    static inline Vec2 GetWorldMousePos() { return GetInstance().__GetMousePos() + Camera::position; }

    InputManager(const InputManager &) = delete;
    InputManager(InputManager &&) = delete;
    void operator=(const InputManager &) = delete;
    void operator=(InputManager &&) = delete;

private:
    InputManager();
    ~InputManager();

    void __Update();

    bool __KeyPress(Key key) const;
    bool __KeyRelease(Key key) const;
    bool __IsKeyDown(Key key) const;

    bool __MousePress(MouseButton button) const;
    bool __MouseRelease(MouseButton button) const;
    bool __IsMouseDown(MouseButton button) const;

    std::int32_t __GetMouseX() const;
    std::int32_t __GetMouseY() const;

    Vec2 __GetMousePos() const;

    bool __QuitRequested() const;

    static InputManager &GetInstance();

    std::int32_t GetKeyIndex(Key key) const;

    std::array<bool, 6> m_mouseState;
    std::array<int32_t, 6> m_mouseUpdate;

    std::array<bool, 416> m_keyState;
    std::array<int32_t, 416> m_keyUpdate;

    bool m_quitRequested = false;
    std::int32_t m_updateCounter = 0;
    std::int32_t m_mouseX = 0;
    std::int32_t m_mouseY = 0;
};