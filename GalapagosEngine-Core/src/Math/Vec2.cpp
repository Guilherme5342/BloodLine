#include "Galapagos/Math/Vec2.hpp"
#include <cmath>

#define M_PI 3.14159265358979323846

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool Vec2::operator==(const Vec2 &other) const
{
    return (x == other.x && y == other.y);
}

bool Vec2::operator!=(const Vec2 &other) const
{
    return !operator==(other);
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
}

void Vec2::operator+=(const Vec2 &other)
{
    x += other.x;
    y += other.y;
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(x - other.x, y - other.y);
}

void Vec2::operator-=(const Vec2 &other)
{
    x -= other.x;
    y -= other.y;
}

Vec2 Vec2::operator*(const float &scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

void Vec2::operator*=(const float &scalar)
{
    x *= scalar;
    y *= scalar;
}

Vec2 Vec2::operator/(const float &scalar) const
{
    return Vec2(x / scalar, y / scalar);
}

void Vec2::operator/=(const float &scalar)
{
    x /= scalar;
    y /= scalar;
}

float Vec2::Magnitude() const
{
    return sqrt((x * x) + (y * y));
}

void Vec2::Normalize()
{
    float m = Magnitude();
    x /= m;
    y /= m;
}

Vec2 Vec2::Normalized() const
{
    float m = Magnitude();
    return Vec2(x / m, y / m);
}

float Vec2::Distance(const Vec2 &other) const
{
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

float Vec2::InclinationRad() const
{
    return atan2(y, x);
}

float Vec2::InclinationRad(const Vec2 &other) const
{
    return atan2(other.y - y, other.x - x);
}

float Vec2::InclinationDeg() const
{
    return atan2(y, x) * 180 / M_PI;
}

float Vec2::InclinationDeg(const Vec2 &other) const
{
    return atan2(other.y - y, other.x - x) * 180 / M_PI;
}

void Vec2::RotateRad(float radians)
{
    float newX = x * cos(radians) - y * sin(radians);
    float newY = x * sin(radians) + y * cos(radians);
    x = newX;
    y = newY;
}

Vec2 Vec2::RotatedRad(float radians) const
{
    return Vec2(x * cos(radians) - y * sin(radians), x * sin(radians) + y * cos(radians));
}

void Vec2::RotateDeg(float angle)
{
    float radians = angle * M_PI / 180;
    RotateRad(radians);
}

Vec2 Vec2::RotatedDeg(float angle) const
{
    float radians = angle * M_PI / 180;
    return RotatedRad(radians);
}

std::ostream &operator<<(std::ostream &stream, const Vec2 &vec2)
{
    stream << "{x: " << vec2.x << ", y: " << vec2.y << "}";
    return stream;
}