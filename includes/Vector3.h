#pragma once

#include <cmath>
#include <math.h>
#include <type_traits>
#include <iostream>

#define FRAC_PI (180 / M_PI)

using namespace std;

struct Vector3 {

public:
	float x, y, z;

	float magnitude() { return sqrt(x * x + y * y + z * z); }

	inline Vector3(float x = 0, float y = 0, float z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Modelo de Classe com Restrição de Tipo
	// O Vector3 só aceita Tipos de Variável que são considerados Aritméticos (int,double,float)
	template<typename T , typename = typename enable_if<is_arithmetic<T>::val,T>::type>
	inline Vector3(T x = 0, T y = 0, T z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline Vector3() {
		x = y = z = 0;
	}

	//template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	inline virtual Vector3 GetRotated(float angle) {
		return Vector3(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val,T>::type>
	static T Angle(const Vector3& from, const Vector3& to) {
		return (T)atan2(to.y - from.y, to.x - from.x);
	}

	
	Vector3 operator+(Vector3 const& vec)  {

		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3 operator*(Vector3 const& vec) {
		return Vector3(x * vec.x, y * vec.y, z * vec.z);
	}

	Vector3 operator-(Vector3 const& vec) {
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 operator/(Vector3 const& vec) {
		return Vector3(x / vec.x, y / vec.y, z / vec.z);
	}


	template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	Vector3 operator*(T const& n) const {
		return Vector3(x * n, y * n, z * n);
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val,T>::type>
	Vector3 operator/(T const& vec) const {
		return Vector3(x / vec, y / vec, z / vec);
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	Vector3 operator*=(T const& n) const {
		Vector3 nVec = Vector3(x, y, z);
		nVec.x *= n;
		nVec.y *= n;
		nVec.z *= n;
		return nVec;
	}


	Vector3 normalized() {
		return Vector3(x / magnitude(), y / magnitude(),z / magnitude());
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val,T>::type>
	static Vector3 Random(T maxX, T maxY) {
		T randomX = (T)rand() % maxX, randomY = (T)rand() % maxY;
		return Vector3(randomX, randomY);
	}


	inline void Translate(Vector3 vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	inline void Translate(T const vec) const {
		x += vec;
		y += vec;
		z += vec;
	}

	friend ostream& operator<<(ostream& out, const Vector3& vec);
	


	
};

struct Vector2 : public Vector3 {

public:
	inline Vector2(float x = 0, float y = 0) : Vector3(x, y, 0) {
		this->z = 0;
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val,T>::type>
	inline Vector2(T x = 0, T y = 0) : Vector3(x, y, 0) {
		this->z = 0;
	}

	Vector2 operator+(Vector3 const& vec) {

		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 operator*(Vector3 const& vec) {
		return Vector2(x * vec.x, y * vec.y);
	}

	Vector2 operator-(Vector3 const& vec) {
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 operator/(Vector3 const& vec) {
		return Vector2(x / vec.x, y / vec.y);
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	Vector2 operator*(T const& vec) const {
		return Vector2((T)(x * vec),(T)(y * vec));
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	Vector2 operator/(T const& vec) const {
		return Vector2((T)(x / vec), (T)(y / vec));
	}

	template<typename T, typename = typename enable_if<is_arithmetic<T>::val, T>::type>
	Vector2 operator*=(T const& n) const {
		Vector2 nVec = Vector2(x, y);
		nVec.x *= n;
		nVec.y *= n;
		return nVec;
	}

	friend ostream& operator<<(ostream& out, const Vector2& vec);

};


inline float Distance(Vector3 a, Vector3 b) {
	return (b - a).magnitude();
}

inline float DotProduct(Vector2 a, Vector3 b) {
	return (a.x * b.x + a.y * b.y);
}