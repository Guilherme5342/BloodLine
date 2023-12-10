#include "Entity/GameObject.h"
#include "Entity/Component.h"

class Minion : public Component
{
public:
    Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    ~Minion() override;

    void Update(float deltaTime) override;
    void NotifyCollision(GameObject &other) override;
    void Render() const override;
    void Shoot(Vec2 target);

    inline bool Is(std::string type) const override { return type == "Minion"; }

private:
    std::weak_ptr<GameObject> m_alienCenter;
    std::int32_t m_hp = 50;
    float m_arc;
};