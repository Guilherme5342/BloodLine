#include "Matrix3.h"
#include "Maths.h"
#include "Vector3.h"
using namespace NCL;
using namespace NCL::Maths;
Matrix3::Matrix3(void)	{
	ToIdentity();
}

Matrix3::Matrix3(float elements[16]) {
	values[0] = elements[0];
	values[1] = elements[1];
	values[2] = elements[2];

	values[3] = elements[4];
	values[4] = elements[5];
	values[5] = elements[6];

	values[6] = elements[8];
	values[7] = elements[9];
	values[8] = elements[10];
}

Matrix3::Matrix3(const Matrix4 &m4) {
	values[0] = m4.values[0];
	values[1] = m4.values[1];
	values[2] = m4.values[2];

	values[3] = m4.values[4];
	values[4] = m4.values[5];
	values[5] = m4.values[6];

	values[6] = m4.values[8];
	values[7] = m4.values[9];
	values[8] = m4.values[10];
}


Matrix3::~Matrix3(void)	{

}

Matrix3 Matrix3::Rotation(float degrees, const Vector3 &inaxis)	 {
	Matrix3 m;

	Vector3 axis = inaxis;

	axis.Normalise();

	float c = cos(Maths::DegreesToRadians(degrees));
	float s = sin(Maths::DegreesToRadians(degrees));

	m.values[0]  = (axis.x * axis.x) * (1.0f - c) + c;
	m.values[1]  = (axis.y * axis.x) * (1.0f - c) + (axis.z * s);
	m.values[2]  = (axis.z * axis.x) * (1.0f - c) - (axis.y * s);

	m.values[3]  = (axis.x * axis.y) * (1.0f - c) - (axis.z * s);
	m.values[4]  = (axis.y * axis.y) * (1.0f - c) + c;
	m.values[5]  = (axis.z * axis.y) * (1.0f - c) + (axis.x * s);

	m.values[6]  = (axis.x * axis.z) * (1.0f - c) + (axis.y * s);
	m.values[7]  = (axis.y * axis.z) * (1.0f - c) - (axis.x * s);
	m.values[8]  = (axis.z * axis.z) * (1.0f - c) + c;

	return m;
}

Matrix3 Matrix3::Scale( const Vector3 &scale )	{
	Matrix3 m;

	m.values[0]  = scale.x;
	m.values[4]  = scale.y;
	m.values[8]  = scale.z;	

	return m;
}


void	Matrix3::ToZero()	{
	for(int i = 0; i < 9; ++i) {
		values[0] = 0.0f;
	}
}

void	Matrix3::ToIdentity() {
	for(int i = 0; i < 9; ++i) {
		values[i] = 0.0f;
	}
	values[0]  = 1.0f;
	values[4]  = 1.0f;
	values[8]  = 1.0f;	
}

//http://staff.city.ac.uk/~sbbh653/publications/euler.pdf
Vector3 Matrix3::ToEuler() const {
	//float h = (float)RadiansToDegrees(atan2(-values[6], values[0]));
	//float b = (float)RadiansToDegrees(atan2(-values[5], values[4]));
	//float a = (float)RadiansToDegrees(asin(values[3]));

	//return Vector3(a, h, b);

	//psi  = x;
	//theta = y;
	//phi = z



	float testVal = abs(values[2]) + 0.00001f;

	if (testVal < 1.0f) {
		float theta1 = -asin(values[2]);
		float theta2 = Maths::PI - theta1;

		float cost1 = cos(theta1);
		float cost2 = cos(theta2);

		float psi1 = Maths::RadiansToDegrees(atan2(values[5] / cost1, values[8] / cost1));
		float psi2 = Maths::RadiansToDegrees(atan2(values[5] / cost2, values[8] / cost2));

		float phi1 = Maths::RadiansToDegrees(atan2(values[1] / cost1, values[0] / cost1));
		float phi2 = Maths::RadiansToDegrees(atan2(values[1] / cost2, values[0] / cost2));

		theta1 = Maths::RadiansToDegrees(theta1);
		theta2 = Maths::RadiansToDegrees(theta2);

		return Vector3(psi1, theta1, phi1);
	}
	else {
		float phi	= 0.0f;	//x


		float theta = 0.0f;	//y
		float psi	= 0.0f;	//z

		float delta = atan2(values[3], values[6]);

		if (values[2] < 0.0f) {
			theta = Maths::PI / 2.0f;
			psi = phi + delta;
		}
		else {
			theta = -Maths::PI / 2.0f;
			psi = phi + delta;
		}

		return Vector3(Maths::RadiansToDegrees(psi), Maths::RadiansToDegrees(theta), Maths::RadiansToDegrees(phi));
	}

	//float sp = values[2];

	//sp = clamp(sp, -1.0f, 1.0f);



	//float theta = -asin(sp);
	//float cp = cos(theta);


	//Vector3 pyr;

	//if (cp > 0.01f) {
	//	pyr.x = RadiansToDegrees(theta);
	//	pyr.y = RadiansToDegrees(atan2(values[1], values[0]));
	//	pyr.z = RadiansToDegrees(atan2(values[5], values[8]));

	//}
	//else {
	//	pyr.x = RadiansToDegrees(theta);

	//	pyr.y = RadiansToDegrees(-atan2(values[3], values[4]));

	//	pyr.z = 0.0f;
	//}

	//return pyr;
}

Matrix3 Matrix3::FromEuler(const Vector3 &euler) {
	Matrix3 m;

	float heading	= Maths::DegreesToRadians(euler.y);
	float attitude	= Maths::DegreesToRadians(euler.x);
	float bank		= Maths::DegreesToRadians(euler.z);

	float ch = cos(heading);
	float sh = sin(heading);
	float ca = cos(attitude);
	float sa = sin(attitude);
	float cb = cos(bank);
	float sb = sin(bank);

	m.values[0] = ch * ca;
	m.values[3] = sh*sb - ch*sa*cb;
	m.values[6] = ch*sa*sb + sh*cb;
	m.values[1] = sa;
	m.values[4] = ca*cb;
	m.values[7] = -ca*sb;
	m.values[2] = -sh*ca;
	m.values[5] = sh*sa*cb + ch*sb;
	m.values[8] = -sh*sa*sb + ch*cb;

	return m;
}
