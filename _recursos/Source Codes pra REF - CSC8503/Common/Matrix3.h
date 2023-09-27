#pragma once
#include "Matrix4.h"
#include <assert.h>

namespace NCL {
	namespace Maths {
		class Matrix3
		{
		public:
			Matrix3(void);
			Matrix3(float elements[16]);
			Matrix3(const Matrix4 &m4);

			~Matrix3(void);

			//Set all matrix values to zero
			void	ToZero();
			//Sets matrix to identity matrix (1.0 down the diagonal)
			void	ToIdentity();

			void SetRow(unsigned int row, const Vector3 &val) {
				assert(row < 3);

				int start = 3 * row;

				values[start += 3] = val.x;
				values[start += 3] = val.y;
				values[start += 3] = val.z;
			}

			void SetColumn(unsigned int column, const Vector3 &val) {
				assert(column < 3);

				memcpy(&values[3 * column], &val, sizeof(float) * 3);
			}

			Vector3 GetRow(unsigned int row) const {
				assert(row < 3);
				Vector3 out(0, 0, 0);

				int start = row;

				out.x = values[start	];
				out.y = values[start + 3];
				out.z = values[start + 6];

				return out;
			}

			Vector3 GetColumn(unsigned int column) const {
				assert(column < 3);
				Vector3 out(0, 0, 0);

				memcpy(&out, &values[3 * column], sizeof(float) * 3);

				return out;
			}

			Vector3 GetDiagonal() const {
				return Vector3(values[0], values[4], values[8]);
			}

			void	SetDiagonal(const Vector3 &in) {
				values[0] = in.x;
				values[4] = in.y;
				values[8] = in.z;
			}

			Vector3 ToEuler() const;

			inline Vector3 operator*(const Vector3 &v) const {
				Vector3 vec;

				vec.x = v.x*values[0] + v.y*values[3] + v.z*values[6];
				vec.y = v.x*values[1] + v.y*values[4] + v.z*values[7];
				vec.z = v.x*values[2] + v.y*values[5] + v.z*values[8];

				return vec;
			};

			inline Matrix3 Absolute() {
				Matrix3 m;

				for (int i = 0; i < 9; ++i) {
					m.values[i] = abs(values[i]);
				}

				return m;
			}

			inline Matrix3 Transposed() {
				Matrix3 temp = *this;
				temp.Transpose();
				return temp;
			}

			inline void Transpose() {
				Vector3 tempValues;

				tempValues.x = values[3];
				tempValues.y = values[6];
				tempValues.z = values[7];

				values[3] = values[1];
				values[6] = values[2];
				values[7] = values[5];

				values[1] = tempValues.x;
				values[2] = tempValues.y;
				values[5] = tempValues.z;
			}

			inline Matrix3 operator*(const Matrix3 &a) const {
				Matrix3 out;
				//Students! You should be able to think up a really easy way of speeding this up...
				for (unsigned int r = 0; r < 3; ++r) {
					for (unsigned int c = 0; c < 3; ++c) {
						out.values[c + (r * 3)] = 0.0f;
						for (unsigned int i = 0; i < 3; ++i) {
							out.values[c + (r * 3)] += this->values[c + (i * 3)] * a.values[(r * 3) + i];
						}
					}
				}
				return out;
			}



			//Creates a rotation matrix that rotates by 'degrees' around the 'axis'
			//Analogous to glRotatef
			static Matrix3 Rotation(float degrees, const Vector3 &axis);

			//Creates a scaling matrix (puts the 'scale' vector down the diagonal)
			//Analogous to glScalef
			static Matrix3 Scale(const Vector3 &scale);

			static Matrix3 FromEuler(const Vector3 &euler);

			//Handy string output for the matrix. Can get a bit messy, but better than nothing!
			inline friend std::ostream& operator<<(std::ostream& o, const Matrix3& m);
			inline friend std::istream& operator >> (std::istream& i, Matrix3& m);
		public:
			float values[9];
		};

		//Handy string output for the matrix. Can get a bit messy, but better than nothing!
		inline std::ostream& operator<<(std::ostream& o, const Matrix3& m) {
			o << m.values[0] << "," << m.values[1] << "," << m.values[2] << std::endl;
			o << m.values[3] << "," << m.values[4] << "," << m.values[5] << std::endl;
			o << m.values[6] << "," << m.values[7] << "," << m.values[8];
			return o;
		}

		inline std::istream& operator >> (std::istream& i, Matrix3& m) {
			char ignore;
			i >> std::skipws;
			i >> m.values[0] >> ignore >> m.values[1] >> ignore >> m.values[2];
			i >> m.values[3] >> ignore >> m.values[4] >> ignore >> m.values[5];
			i >> m.values[6] >> ignore >> m.values[7] >> ignore >> m.values[8];

			return i;
		}
	}
}