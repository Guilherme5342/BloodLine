#pragma once
#include "Galapagos/Core/State.hpp"

class MainMenuState : public State
{
public:
    MainMenuState();
    ~MainMenuState();

    void LoadAssets();
    void Update(float deltaTime);
    void Render() const;

    void Start();
    void Pause();
    void Resume();
private:
};