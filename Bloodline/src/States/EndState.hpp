#pragma once
#include "Galapagos/Core/State.hpp"
#include "Galapagos/Core/Music.hpp"

class EndState : public State
{
public:
    EndState();
    ~EndState() override;

    void LoadAssets() override;
    void Update(float deltaTime) override;
    void Render() const override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music m_music;
};