#pragma once
#include <vector>
#include <memory>

#include "Galapagos/Core/State.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/Music.hpp"
#include "Galapagos/Utils/Timer.hpp"

class StageState : public State
{
public:
    StageState();
    ~StageState() override;

    void LoadAssets() override;
    void Update(float deltaTime) override;
    void Render() const override;

    void Start() override;
    void Pause() override {};
    void Resume() override;

private:
    Music m_music;
    Timer m_timer;
};
