#pragma once
#include <vector>
#include <memory>

#include "Galapagos/Core/State.hpp"
#include "Galapagos/Components/AnimatedSprite.hpp"
#include "Galapagos/Core/Music.hpp"
#include "Galapagos/Utils/Timer.hpp"

#include "GameDefines/GlobalDefinitions.hpp"


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

    void LoadEnemy(Vec2 pos, Vec2 size, std::weak_ptr<GameObject> player);
    void LoadTMX(std::string file);

    Music m_music;
    Timer m_timer;
};
