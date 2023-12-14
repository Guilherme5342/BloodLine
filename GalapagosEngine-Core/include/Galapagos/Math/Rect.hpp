#pragma once

#include <iostream>
#include "Vec2.hpp"

struct Rect
{
    float x = 0, y = 0, w = 0, h = 0;

    Rect();
    Rect(float x, float y, float w, float h);

    Vec2 GetCenter() const;
    void SetCenter(Vec2 pos);
    void SetSize(float x, float y);
    void SetSize(Vec2 size);
    Rect Scaled(float x, float y) const;
    Rect Scaled(Vec2 scale) const;
    float Distance(const Rect &other) const;
    float Distance(const Vec2 &other) const;
    bool IsColliding(const Vec2 &point) const;

    Rect GetIntersection(Rect& otherRect);
};

std::ostream &operator<<(std::ostream &stream, const Rect &rect);