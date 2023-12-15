#pragma once
#include <vector>
#include <memory>

#include "Galapagos/Core/State.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Core/Music.hpp"
#include "Galapagos/Utils/Timer.hpp"

#include "GameDefines/GlobalDefinitions.hpp"
#include "GameDefines/ColorDefinitions.hpp"

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

    void FixedUpdate(float fixedDt) override;
private:
    Music m_music;
    Timer m_timer;
};
