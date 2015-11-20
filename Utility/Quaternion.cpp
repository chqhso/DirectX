#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include <cmath>


Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
Quaternion::Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
Quaternion::Quaternion(const Vector3& v, float angle){
	float _sin = sin(angle / 2.0f);
	x = _sin * v.x;
	y = _sin * v.y;
	z = _sin * v.z;
	w = cos(angle / 2.0f);
}
Quaternion::Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
Quaternion::Quaternion(const Matrix4x4& mat){
	float tr = mat.m[0][0] + mat.m[1][1] + mat.m[2][2] + mat.m[3][3];
	if( tr >= 1.0f){
		float fourD = 2.0f * sqrt(tr);
		x = (mat.m[1][2] - mat.m[2][1]) / fourD;
		y = (mat.m[2][0] - mat.m[0][2]) / fourD;
		z = (mat.m[0][1] - mat.m[1][0]) / fourD;
		w = fourD / 4.0f;
		return;
	}
	int i = 0;
	if(mat.m[0][0] <= mat.m[1][1]){
		i = 1;
	}
	if(mat.m[2][2] > mat.m[i][i]){
		i = 2;
	}
	int j = (i + 1) % 3;
	int k = (j + 1) % 3;
	tr = mat.m[i][i] - mat.m[j][j] - mat.m[k][k] + 1.0f;
	float fourD = 2.0f * sqrt(tr);
	float qa[4];
	qa[i] = fourD / 4.0f;
	qa[j] = (mat.m[j][i] + mat.m[i][j]) / fourD;
	qa[k] = (mat.m[k][i] + mat.m[i][k]) / fourD;
	qa[3] = (mat.m[j][k] - mat.m[k][j]) / fourD;
	x = qa[0];
	y = qa[1];
	z = qa[2];
	w = qa[3];
}
Quaternion::Quaternion(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
Quaternion::~Quaternion() {}

float Quaternion::Dot(const Quaternion& q){
	return Dot(*this, q);
}
float Quaternion::Length(){
	return Length(*this);
}
Quaternion Quaternion::Normalized(){
	return Normalized(*this);
}
void Quaternion::Normalize(){
	*this = Normalized();
}
Matrix4x4 Quaternion::Rotate(){
	// TODO
	return Matrix4x4::Identity();
	//return Rotate(*this);
}

float		Quaternion::Dot			(const Quaternion& q1,		const Quaternion& q2){
	return q1.x * q2.x +
		   q1.y * q2.y +
		   q1.z * q2.z +
		   q1.w * q2.w;
}
float		Quaternion::Length		(const Quaternion& q){
	return (float)sqrt(Dot(q, q));
}
Quaternion	Quaternion::Normalized	(const Quaternion& q){
	Quaternion result = q;
	float len = Length(result);
	if(len != 0)
		result /= len;
	return result;
}
Quaternion	Quaternion::Slerp		(const Quaternion& start,	const Quaternion& end,	float t){
	float _cos = Dot(start, end);
	Quaternion t2 = end;
	if(_cos < 0.0f){
		_cos = -_cos;
		t2 = -end;
	}
	float k0 = 1.0f - t;
	float k1 = t;
	if((1.0f - _cos) > 0.001f){
		float theta = (float)acos(_cos);
		k0 = (float)(sin(theta * k0) / sin(theta));
		k1 = (float)(sin(theta * k1) / sin(theta));
	}
	return start * k0 + t2 * k1;
}
/** Matrix4x4∑Œ ¿Ãµø
Matrix4x4	Quaternion::Rotate		(const Quaternion& q){
	float xx = q.x * q.x * 2.0f;
	float yy = q.y * q.y * 2.0f;
	float zz = q.z * q.z * 2.0f;
	float xy = q.x * q.y * 2.0f;
	float xz = q.x * q.z * 2.0f;
	float yz = q.y * q.z * 2.0f;
	float wx = q.w * q.x * 2.0f;
	float wy = q.w * q.y * 2.0f;
	float wz = q.w * q.z * 2.0f;

	Matrix4x4 result(
			1.0f - yy - zz,		   xy + wz,		   xz - wy, 0.0f,
				   xy - wz, 1.0f - xx - zz,		   yz + wz, 0.0f,
				   xz + wy,		   yz - wx, 1.0f - xx - yy, 0.0f,
				      0.0f,			  0.0f,			  0.0f, 1.0f
		);
	return result;
}
Matrix4x4	Quaternion::Rotate		(const Vector3& v,			float angle){
	return Rotate(Quaternion(v, angle));
}
*/

Quaternion operator + (const Quaternion& q){
	return q;
}
Quaternion operator - (const Quaternion& q){
	return Quaternion(-q.x, -q.y, -q.z, -q.w);
}

Quaternion& operator += (Quaternion& q1, const Quaternion q2){
	q1.x += q2.x;
	q1.y += q2.y;
	q1.z += q2.z;
	q1.w += q2.w;
	
	return q1;
}
Quaternion& operator -= (Quaternion& q1, const Quaternion q2){
	q1 += -q2;
	return q1;
}
Quaternion& operator *= (Quaternion& q, float s){
	q.x *= s;
	q.y *= s;
	q.z *= s;
	q.w *= s;
	return q;
}
Quaternion& operator /= (Quaternion& q, float s){
	return q *= 1.0f / s;
}
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2){
	Quaternion result(
			 q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x,
			-q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y,
			 q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z,
			-q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w
		);

	return q1 = result;
	return q1;
}

Quaternion operator + (const Quaternion& q1, const Quaternion& q2){
	Quaternion result = q1;
	return result += q2;
}
Quaternion operator - (const Quaternion& q1, const Quaternion& q2){
	Quaternion result = q1;
	return result -= q2;
}
Quaternion operator * (const Quaternion& q1, const Quaternion& q2){
	Quaternion result = q1;
	return result *= q2;
}
Quaternion operator * (const Quaternion& q, float s){
	Quaternion result = q;
	return result *= s;
}
Quaternion operator * (float s, const Quaternion& q){
	Quaternion result = q;
	return result *= s;
}
Quaternion operator / (const Quaternion& q, float s){
	Quaternion result = q;
	return result /= s;
}