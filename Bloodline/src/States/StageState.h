#pragma once
#include <vector>
#include <memory>

#include "Galapagos/Core/State.h"
#include "Galapagos/Components/Sprite.h"
#include "Galapagos/Core/Music.h"
#include "Galapagos/Utils/Timer.h"

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
