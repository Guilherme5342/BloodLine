/******************************************************************************
Class:Vector3
Implements:
Author:Rich Davison
Description:VERY simple Vector3 class.

-_-_-_-_-_-_-_,------,
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""

*//////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cmath>
#include <iostream>
#include <algorithm>

namespace NCL {
	namespace Maths {
		class Vector3 {
		public:
			union {
				struct {
					float x;
					float y;
					float z;
				};
				float array[3];
			};
		public:
			Vector3(void) {
				ToZero();
			}

			Vector3(const float x, const float y, const float z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}

			~Vector3(void) {}

			Vector3 Normalised() const {
				Vector3 temp(x, y, z);
				temp.Normalise();
				return temp;
			}

			void			Normalise() {
				float length = Length();

				if (length != 0.0f) {
					length = 1.0f / length;
					x = x * length;
					y = y * length;
					z = z * length;
				}
			}

			void		ToZero() {
				x = y = z = 0.0f;
			}

			float			Length() const {
				return sqrt((x*x) + (y*y) + (z*z));
			}

			void			Invert() {
				x = -x;
				y = -y;
				z = -z;
			}

			Vector3			Inverse() const {
				return Vector3(-x, -y, -z);
			}

			float			GetMaxElement() const {
				float v = x;
				if (y > v) {
					v = y;
				}
				if (z > v) {
					v = z;
				}
				return v;
			}

			float			GetAbsMaxElement() const {
				float v = abs(x);
				if (abs(y) > v) {
					v = abs(y);
				}
				if (abs(z) > v) {
					v = abs(z);
				}
				return v;
			}

			static float	Dot(const Vector3 &a, const Vector3 &b) {
				return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
			}

			static Vector3	Cross(const Vector3 &a, const Vector3 &b) {
				return Vector3((a.y*b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x*b.y) - (a.y*b.x));
			}



			inline friend std::ostream& operator<<(std::ostream& o, const Vector3& v) {
				o << "Vector3(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
				return o;
			}

			inline Vector3  operator+(const Vector3  &a) const {
				return Vector3(x + a.x, y + a.y, z + a.z);
			}

			inline Vector3  operator-(const Vector3  &a) const {
				return Vector3(x - a.x, y - a.y, z - a.z);
			}

			inline Vector3  operator-() const {
				return Vector3(-x, -y, -z);
			}

			inline void operator+=(const Vector3  &a) {
				x += a.x;
				y += a.y;
				z += a.z;
			}

			inline void operator-=(const Vector3  &a) {
				x -= a.x;
				y -= a.y;
				z -= a.z;
			}


			inline void operator*=(const Vector3  &a) {
				x *= a.x;
				y *= a.y;
				z *= a.z;
			}

			inline void operator/=(const Vector3  &a) {
				x /= a.x;
				y /= a.y;
				z /= a.z;
			}

			inline void operator*=(float f) {
				x *= f;
				y *= f;
				z *= f;
			}

			inline void operator/=(float f) {
				x /= f;
				y /= f;
				z /= f;
			}

			inline float operator[](int i) const {
				return array[i];
			}

			inline float& operator[](int i) {
				return array[i];
			}

			inline Vector3  operator*(const float a) const {
				return Vector3(x * a, y * a, z * a);
			}

			inline Vector3  operator*(const Vector3  &a) const {
				return Vector3(x * a.x, y * a.y, z * a.z);
			}

			inline Vector3  operator/(const Vector3  &a) const {
				return Vector3(x / a.x, y / a.y, z / a.z);
			};

			inline Vector3  operator/(const float v) const {
				return Vector3(x / v, y / v, z / v);
			};

			inline bool	operator==(const Vector3 &A)const { return (A.x == x && A.y == y && A.z == z) ? true : false; };
			inline bool	operator!=(const Vector3 &A)const { return (A.x == x && A.y == y && A.z == z) ? false : true; };
		};
	}
}
