#include "Galapagos/Math/Rect.hpp"

Rect::Rect() {}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Vec2 Rect::GetCenter() const
{
    return Vec2(x + w / 2, y + h / 2);
}

void Rect::SetCenter(Vec2 pos)
{
    this->x = pos.x - w / 2;
    this->y = pos.y - h / 2;
}

void Rect::SetSize(float x, float y)
{
    Vec2 center = GetCenter();
    this->w = x;
    this->h = y;
    SetCenter(center);
}

void Rect::SetSize(Vec2 size)
{
    SetSize(size.x, size.y);
}

Rect Rect::Scaled(float x, float y) const
{
    Rect scaledRect = *this;
    Vec2 center = scaledRect.GetCenter();
    scaledRect.w *= x;
    scaledRect.h *= y;
    scaledRect.SetCenter(center);
    return scaledRect;
}

Rect Rect::Scaled(Vec2 scale) const
{
    return Scaled(scale.x, scale.y);
}

float Rect::Distance(const Rect &other) const
{
    return this->GetCenter().Distance(other.GetCenter());
}

float Rect::Distance(const Vec2 &other) const
{
    return this->GetCenter().Distance(other);
}

bool Rect::IsColliding(const Vec2 &point) const
{
    return point.x >= x && point.x <= (x + w) && point.y >= y && point.y <= (y + h);
}

std::ostream &operator<<(std::ostream &stream, const Rect &rect)
{
    stream << "{x: " << rect.x << ", y: " << rect.y << ", w: " << rect.w << ", h: " << rect.h << "}";
    return stream;
}