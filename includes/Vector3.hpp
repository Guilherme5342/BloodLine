#pragma once

#include <cmath>
#include <math.h>
#include <type_traits>
#include <iostream>

#define FRAC_PI (180 / M_PI)

using namespace std;

struct Vector3
{

public:
	float x, y, z;

	float magnitude() { return sqrt(x * x + y * y + z * z); }

	inline Vector3()
	{
		x = y = z = 0;
	}
	inline Vector3(float x, float y, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		// cout << "Vetor Y: " << this->y << endl;
	}

	// Modelo de Classe com Restri��o de Tipo
	// O Vector3 s� aceita Tipos de Vari�vel que s�o considerados Aritm�ticos (int,double,float)

	// template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	inline virtual Vector3 GetRotated(float angle)
	{
		return Vector3(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
	}

	template <typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	static T Angle(const Vector3 &from, const Vector3 &to)
	{
		return (T)atan2(to.y - from.y, to.x - from.x);
	}

	Vector3 operator+(Vector3 const &vec)
	{

		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3 operator*(Vector3 const &vec)
	{
		return Vector3(x * vec.x, y * vec.y, z * vec.z);
	}

	Vector3 operator-(Vector3 const &vec)
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 operator/(Vector3 const &vec)
	{
		return Vector3(x / vec.x, y / vec.y, z / vec.z);
	}

	Vector3 operator*(const float n) const
	{
		return Vector3(x * n, y * n, z * n);
	}

	Vector3 operator/(const float vec) const
	{
		Vector3 nVec;
		nVec.x = x / vec;
		nVec.y = y / vec;
		nVec.z = z / vec;
		return nVec;
	}

	template <typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	Vector3 &operator+=(const T n)
	{
		this->x += n;
		this->y += n;
		this->z += n;
		return *this;
	}

	template <typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	Vector3 &operator*=(const T n)
	{
		this->x *= n;
		this->y *= n;
		this->z *= n;
		return *this;
	}

	Vector3 normalized()
	{
		return Vector3(x / magnitude(), y / magnitude(), z / magnitude());
	}

	template <typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	static Vector3 Random(T maxX, T maxY)
	{
		T randomX = (T)rand() % maxX, randomY = (T)rand() % maxY;
		return Vector3(randomX, randomY);
	}

	inline void Translate(Vector3 vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	template <typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	inline void Translate(T const vec) const
	{
		x += vec;
		y += vec;
		z += vec;
	}

	/*static Vector3 Clamp(Vector3 target, Vector3 a, Vector3 b) {
		return Vector3(std::max(a, std::min(b, target)));
	}*/

	friend ostream &operator<<(ostream &out, const Vector3 &vec);
};

struct Vector2 : public Vector3
{

public:
	inline Vector2() : Vector3()
	{
		this->z = 0;
	}
	inline Vector2(float x, float y) : Vector3(x, y, 0)
	{
		this->z = 0;
	}

	inline Vector2 GetRotated2(float rad)
	{
		return Vector2(x * cos(rad) - y * sin(rad), y * cos(rad) + x * sin(rad));
	}

	Vector2 operator+(Vector3 const &vec)
	{

		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 operator+(const float num) const
	{

		return Vector2(x + num, y + num);
	}

	Vector2 operator*(Vector3 const &vec)
	{
		return Vector2(x * vec.x, y * vec.y);
	}

	Vector2 operator-(Vector3 const &vec)
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 operator/(Vector3 const &vec)
	{
		return Vector2(x / vec.x, y / vec.y);
	}

	Vector2 operator*(const float vec) const
	{
		return Vector2(this->x * vec, this->y * vec);
	}

	Vector2 operator/(const float vec) const
	{
		return Vector2(this->x / vec, this->y / vec);
	}

	Vector2 &operator+=(const Vector2 &vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	Vector2 &operator*=(const Vector2 &vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
		return *this;
	}

	Vector2 &operator*=(const float vec)
	{
		this->x *= vec;
		this->y *= vec;
		return *this;
	}

	float GetMagnitude()
	{
		return sqrt(x * x + y * y);
	}

	//template <typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	static float Angle(const Vector2& from, const Vector2& to)
	{
		return (float)atan2(to.y - from.y, to.x - from.x);
	}

	static Vector2 DirectionFrom(float angle) {
		return Vector2(cos(angle), sin(angle));
	}

	friend ostream &operator<<(ostream &out, const Vector2 &vec);
};

inline float Distance(Vector3 a, Vector3 b)
{
	return (b - a).magnitude();
}

inline float DotProduct(Vector2 a, Vector3 b)
{
	return (a.x * b.x + a.y * b.y);
}
