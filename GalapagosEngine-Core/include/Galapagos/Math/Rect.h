#pragma once

#include <iostream>
#include "Vec2.h"

struct Rect
{
    float x = 0, y = 0, w = 0, h = 0;

    Rect();
    Rect(float x, float y, float w, float h);

    Vec2 GetCenter() const;
    void SetCenter(Vec2 pos);
    void Scale(float x, float y);
    void Scale(Vec2 scale);
    float Distance(const Rect &other) const;
    float Distance(const Vec2 &other) const;
    bool IsColliding(const Vec2 &point) const;
};

std::ostream &operator<<(std::ostream &stream, const Rect &rect);