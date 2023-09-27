/******************************************************************************
Class:Quaternion
Implements:
Author:Rich Davison
Description:VERY simple Quaternion class. Students are encouraged to modify 
this as necessary...if they dare.

Quaternions aren't really discussed much in the graphics module, but the 
MD5Mesh class uses them internally, as MD5 files store their rotations
as quaternions.

I hate Quaternions.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Matrix4.h"
#include "Matrix3.h"

namespace NCL {
	namespace Maths {
		class Matrix4;

		class Quaternion {
		public:
			union {
				struct {
					float x;
					float y;
					float z;
					float w;
				};
				float array[4];
			};
		public:
			Quaternion(void);
			Quaternion(float x, float y, float z, float w);
			Quaternion(const Vector3& vector, float w);

			~Quaternion(void);

			void	Normalise();
			Matrix4 ToMatrix4() const;
			Matrix3 ToMatrix3() const;

			Quaternion	Conjugate() const;
			void		CalculateW();	//builds 4th component when loading in shortened, 3 component quaternions


			void RotateByWorldAngles(const Vector3 angles);

			static Quaternion EulerAnglesToQuaternion(float pitch, float yaw, float roll);
			static Quaternion AxisAngleToQuaterion(const Vector3& vector, float degrees);

			Vector3 ToEuler() const;

			static void RotatePointByQuaternion(const Quaternion &q, Vector3 &point);

			static Quaternion FromMatrix(const Matrix4 &m);
			static Quaternion FromMatrix(const Matrix3 &m);

			static float Dot(const Quaternion &a, const Quaternion &b);


			static Quaternion	Lerp(const Quaternion &from, const Quaternion &to, float by);
			static Quaternion	Slerp(const Quaternion &from, const Quaternion &to, float by);

			inline bool  operator ==(const Quaternion &from)	const {
				if (x != from.x || y != from.y || z != from.z || w != from.w) {
					return false;
				}
				return true;
			}

			inline bool  operator !=(const Quaternion &from)	const {
				if (x != from.x || y != from.y || z != from.z || w != from.w) {
					return true;
				}
				return false;
			}

			inline Quaternion  operator *(const Quaternion &b)	const {
				return Quaternion(
					(x * b.w) + (w * b.x) + (y * b.z) - (z * b.y),
					(y * b.w) + (w * b.y) + (z * b.x) - (x * b.z),
					(z * b.w) + (w * b.z) + (x * b.y) - (y * b.x),
					(w * b.w) - (x * b.x) - (y * b.y) - (z * b.z)
				);
			}

			inline Vector3		operator *(const Vector3 &a)	const {
				Vector3 uv, uuv;
				Vector3 qvec(x, y, z);
				uv = -Vector3::Cross(qvec, a);
				uuv = -Vector3::Cross(qvec, uv);
				uv *= (2.0f * w);
				uuv *= 2.0f;

				return a + (uv + uuv);

				//float xxzz = x*x - z*z;
				//float wwyy = w*w - y*y;

				//float xw2 = x*w*2.0f;
				//float xy2 = x*y*2.0f;
				//float xz2 = x*z*2.0f;
				//float yw2 = y*w*2.0f;
				//float yz2 = y*z*2.0f;
				//float zw2 = z*w*2.0f;

				//return Vector3(
				//	(xxzz + wwyy)*a.x		+ (xy2 + zw2)*a.y		+ (xz2 - yw2)*a.z,
				//	(xy2 - zw2)*a.x			+ (y*y+w*w-x*x-z*z)*a.y	+ (yz2 + xw2)*a.z,
				//	(xz2 + yw2)*a.x			+ (yz2 - xw2)*a.y		+ (wwyy - xxzz)*a.z
				//	);



			}

			inline Quaternion  operator *(const float &a)		const {
				return Quaternion(x*a, y*a, z*a, w*a);
			}

			inline Quaternion  operator *=(const float &a) {
				*this = *this * a;
				return *this;
			}

			inline Quaternion  operator -()	const {
				return Quaternion(-x, -y, -z, -w);
			}

			inline Quaternion  operator -(const Quaternion &a)	const {
				return Quaternion(x - a.x, y - a.y, z - a.z, w - a.w);
			}

			inline Quaternion  operator -=(const Quaternion &a) {
				*this = *this - a;
				return *this;
			}

			inline Quaternion  operator +(const Quaternion &a)	const {
				return Quaternion(x + a.x, y + a.y, z + a.z, w + a.w);
			}

			inline Quaternion  operator +=(const Quaternion &a) {
				*this = *this + a;
				return *this;
			}

			inline float operator[](const int i) const {
				return array[i];
			}

			inline friend std::ostream& operator<<(std::ostream& o, const Quaternion& q);
			inline friend std::istream& operator >> (std::istream& i, Quaternion &v);
		};

		std::ostream& operator<<(std::ostream& o, const Quaternion& q) {
			o << q.x; o << ",";
			o << q.y; o << ",";
			o << q.z; o << ",";
			o << q.w;
			return o;
		}

		std::istream& operator >> (std::istream& i, Quaternion &v) {
			char ignore;
			i >> std::skipws >> v.x >> ignore >> v.y >> ignore >> v.z >> ignore >> v.w >> std::noskipws;
			return i;
		}
	}
}