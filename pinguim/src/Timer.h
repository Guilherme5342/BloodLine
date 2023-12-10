#pragma once

class Timer
{
public:
    inline Timer() : m_time(0) {}

    inline void Update(float deltaTime) { m_time += deltaTime; }
    inline void Restart() { m_time = 0; }
    inline float Get() const { return m_time; }

private:
    float m_time = 0;
};