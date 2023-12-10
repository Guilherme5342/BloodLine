#pragma once
#include <vector>
#include <memory>

#include "State.h"
#include "Components/Sprite.h"
#include "Components/Music.h"
#include "Timer.h"

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
