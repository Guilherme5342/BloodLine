#pragma once
#include <iostream>

struct Vec2
{
    float x = 0, y = 0;

    Vec2();
    Vec2(float x, float y);

    bool operator==(const Vec2 &other) const;
    bool operator!=(const Vec2 &other) const;

    Vec2 operator+(const Vec2 &other) const;
    void operator+=(const Vec2 &other);

    Vec2 operator-(const Vec2 &other) const;
    void operator-=(const Vec2 &other);

    Vec2 operator*(const float &scalar) const;
    void operator*=(const float &scalar);

    Vec2 operator/(const float &scalar) const;
    void operator/=(const float &scalar);

    float Magnitude() const;
    void Normalize();
    Vec2 Normalized() const;
    float Distance(const Vec2 &other) const;
    float InclinationRad() const;
    float InclinationRad(const Vec2 &other) const;
    float InclinationDeg() const;
    float InclinationDeg(const Vec2 &other) const;
    void RotateRad(float radians);
    Vec2 RotatedRad(float radians) const;
    void RotateDeg(float angle);
    Vec2 RotatedDeg(float angle) const;
};

std::ostream &operator<<(std::ostream &stream, const Vec2 &vec2);