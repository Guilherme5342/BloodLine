#pragma once
#include <memory>
#include <vector>

class GameObject;
class State
{
public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() const = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void FixedUpdate(float fixedDt);

    virtual std::weak_ptr<GameObject> AddObject(GameObject *object);
    virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject *object);

    inline bool PopRequested() const { return m_popRequested; }
    inline bool QuitRequested() const { return m_quitRequested; }

protected:
    virtual void StartArray();
    virtual void FixedUpdateArray(float fixedDt);
    virtual void UpdateArray(float deltaTime);
    virtual void RenderArray() const;

    bool m_popRequested = false;
    bool m_quitRequested = false;
    bool m_started = false;

    std::vector<std::shared_ptr<GameObject>> m_objectArray;
};