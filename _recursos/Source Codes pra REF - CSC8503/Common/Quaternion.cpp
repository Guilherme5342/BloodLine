#include "Quaternion.h"
#include "Matrix3.h"
#include "Maths.h"
#include <algorithm>

using namespace NCL;
using namespace NCL::Maths;

Quaternion::Quaternion(void)
{
	x = y = z = 0.0f;
	w = 1.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(const Vector3& vector, float w) {
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = w;
}

Quaternion::~Quaternion(void)
{
}

float Quaternion::Dot(const Quaternion &a,const Quaternion &b){
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

void Quaternion::Normalise(){
	float magnitude = sqrt(x*x + y*y + z*z + w*w);

	if(magnitude > 0.0f){
		float t = 1.0f / magnitude;

		x *= t;
		y *= t;
		z *= t;
		w *= t;
	}
}

Matrix4 Quaternion::ToMatrix4() const{
	return Matrix4(ToMatrix3());
}

Matrix3 Quaternion::ToMatrix3() const {
	Matrix3 mat;

	float yy = y*y;
	float zz = z*z;
	float xy = x*y;
	float zw = z*w;
	float xz = x*z;
	float yw = y*w;
	float xx = x*x;
	float yz = y*z;
	float xw = x*w;

	mat.values[0] = 1 - 2 * yy - 2 * zz;
	mat.values[1] = 2 * xy + 2 * zw;
	mat.values[2] = 2 * xz - 2 * yw;

	mat.values[3] = 2 * xy - 2 * zw;
	mat.values[4] = 1 - 2 * xx - 2 * zz;
	mat.values[5] = 2 * yz + 2 * xw;

	mat.values[6] = 2 * xz + 2 * yw;
	mat.values[7] = 2 * yz - 2 * xw;
	mat.values[8] = 1 - 2 * xx - 2 * yy;

	return mat;
}

//http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/
//VERIFIED AS CORRECT - Pitch and roll are changed around as the above uses x as 'forward', whereas we use -z
Quaternion Quaternion::EulerAnglesToQuaternion(float roll, float yaw, float pitch)	{
	float cos1	= (float)cos(Maths::DegreesToRadians(yaw   * 0.5f));
	float cos2  = (float)cos(Maths::DegreesToRadians(pitch * 0.5f));
	float cos3  = (float)cos(Maths::DegreesToRadians(roll  * 0.5f));

	float sin1	= (float)sin(Maths::DegreesToRadians(yaw   * 0.5f));
	float sin2	= (float)sin(Maths::DegreesToRadians(pitch * 0.5f));
	float sin3	= (float)sin(Maths::DegreesToRadians(roll  * 0.5f));

	Quaternion q;

	q.x = (sin1 * sin2 * cos3) + (cos1 * cos2 * sin3);
	q.y = (sin1 * cos2 * cos3) + (cos1 * sin2 * sin3);
	q.z = (cos1 * sin2 * cos3) - (sin1 * cos2 * sin3);
	q.w = (cos1 * cos2 * cos3) - (sin1 * sin2 * sin3);

	return q;
};

Quaternion Quaternion::AxisAngleToQuaterion(const Vector3& vector, float degrees)	{
	float theta = (float)Maths::DegreesToRadians(degrees);
	float result = (float)sin( theta / 2.0f );

	return Quaternion((float)(vector.x * result), (float)(vector.y * result), (float)(vector.z * result), (float)cos( theta / 2.0f ));
}

void Quaternion::CalculateW()	{
	w = 1.0f - (x*x)-(y*y)-(z*z);
	if(w < 0.0f) {
		w = 0.0f;
	}
	else{
		w = - sqrt(w);
	}
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion(-x,-y,-z,w);
}

Quaternion Quaternion::FromMatrix(const Matrix4 &m) {
	Quaternion q;
	//
	//q.x = sqrt( max( 0.0f, (1.0f + m.values[0] - m.values[5] - m.values[10]) ) ) / 2.0f;
	//q.y = sqrt( max( 0.0f, (1.0f - m.values[0] + m.values[5] - m.values[10]) ) ) / 2.0f;
	//q.z = sqrt( max( 0.0f, (1.0f - m.values[0] - m.values[5] + m.values[10]) ) ) / 2.0f;

	//q.x = (float)_copysign( q.x, m.values[9] - m.values[6] );
	//q.y = (float)_copysign( q.y, m.values[2] - m.values[8] );
	//q.z = (float)_copysign( q.z, m.values[4] - m.values[1] );

	q.w = sqrt(std::max(0.0f, (1.0f + m.values[0] + m.values[5] + m.values[10])))  * 0.5f;

	if (abs(q.w) < 0.0001f) {
		q.x = sqrt( std::max( 0.0f, (1.0f + m.values[0] - m.values[5] - m.values[10]) ) ) / 2.0f;
		q.y = sqrt( std::max( 0.0f, (1.0f - m.values[0] + m.values[5] - m.values[10]) ) ) / 2.0f;
		q.z = sqrt( std::max( 0.0f, (1.0f - m.values[0] - m.values[5] + m.values[10]) ) ) / 2.0f;

		q.x = (float)_copysign( q.x, m.values[9] - m.values[6] );
		q.y = (float)_copysign( q.y, m.values[2] - m.values[8] );
		q.z = (float)_copysign( q.z, m.values[4] - m.values[1] );
	}
	else {
		float qrFour = 4.0f * q.w;
		float qrFourRecip = 1.0f / qrFour;

		q.x = (m.values[6] - m.values[9]) * qrFourRecip;
		q.y = (m.values[8] - m.values[2]) * qrFourRecip;
		q.z = (m.values[1] - m.values[4]) * qrFourRecip;
	}
	
	return q;
}

Quaternion Quaternion::FromMatrix(const Matrix3 &m) {
	Quaternion q;

	//q.w = sqrt(max(0.0f, (1.0f + m.values[0] + m.values[4] + m.values[8]))) / 2.0f;
	//q.x = sqrt(max(0.0f, (1.0f + m.values[0] - m.values[4] - m.values[8]))) / 2.0f;
	//q.y = sqrt(max(0.0f, (1.0f - m.values[0] + m.values[4] - m.values[8]))) / 2.0f;
	//q.z = sqrt(max(0.0f, (1.0f - m.values[0] - m.values[4] + m.values[8]))) / 2.0f;

	//q.x = (float)_copysign(q.x, m.values[7] - m.values[5]);
	//q.y = (float)_copysign(q.y, m.values[2] - m.values[6]);
	//q.z = (float)_copysign(q.z, m.values[3] - m.values[1]);

	q.w = sqrt(std::max(0.0f, (1.0f + m.values[0] + m.values[4] + m.values[8]))) * 0.5f;

	float qrFour = 4.0f * q.w;
	float qrFourRecip = 1.0f / qrFour;

	q.x = (m.values[5] - m.values[7]) * qrFourRecip;
	q.y = (m.values[6] - m.values[2]) * qrFourRecip;
	q.z = (m.values[1] - m.values[3]) * qrFourRecip;

	return q;
}

void Quaternion::RotateByWorldAngles(const Vector3 angles) {

	//	orientation = orientation + (Quaternion(angVel * dt * 0.5f, 0.0f) * orientation);
}

Quaternion Quaternion::Lerp(const Quaternion &from, const Quaternion &to, float by) {
	Quaternion temp = to;

	float dot = Quaternion::Dot(from,to);

	if(dot < 0.0f) {
		temp = -to;
	}

	return (from * (1.0f - by)) + (temp * by);
}

Quaternion Quaternion::Slerp(const Quaternion &from, const Quaternion &to, float by) {
	Quaternion temp = to;

	float dot = Quaternion::Dot(from,to);

	if(dot < 0.0f) {
		temp = -to;
	}

	return (from * (cos(by))) + (to * (1.0f - cos(by)));
}

//http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
//Verified! Different values to above, due to difference between x/z being 'forward'
Vector3 Quaternion::ToEuler() const {
	Vector3 euler;

	float t = x*y + z*w;

	if (t > 0.4999) {
		euler.z = Maths::RadiansToDegrees(Maths::PI / 2.0f);
		euler.y = Maths::RadiansToDegrees(2.0f * atan2(x, w));
		euler.x = 0.0f;

		return euler;
	}

	if (t < -0.4999) {
		euler.z = -Maths::RadiansToDegrees(Maths::PI / 2.0f);
		euler.y = -Maths::RadiansToDegrees(2.0f * atan2(x, w));
		euler.x = 0.0f;
		return euler;
	}

	float sqx = x*x;
	float sqy = y*y;
	float sqz = z*z;

	euler.z = Maths::RadiansToDegrees(asin(2 * t));
	euler.y = Maths::RadiansToDegrees(atan2(2 * y*w - 2 * x*z, 1.0f - 2 * sqy - 2 * sqz));
	euler.x = Maths::RadiansToDegrees(atan2(2 * x*w - 2 * y*z, 1.0f - 2 * sqx - 2.0f*sqz));

	return euler;
}