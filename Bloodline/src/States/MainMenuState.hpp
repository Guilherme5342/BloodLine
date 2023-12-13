#pragma once
#include "Galapagos/Core/State.hpp"
#include "Galapagos/Core/Music.hpp"
#include "Galapagos/Components/ParticleEmmiter.hpp"

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
    Music m_music;
    ParticleEmmiter* m_emmiter;
    ParticleConfig m_particleConfig;
};