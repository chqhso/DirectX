#ifndef QUATERNION_H
#define QUATERNION_H

struct Vector3;
struct Vector4;
struct Matrix4x4;

struct Quaternion{
public:
	float x, y, z, w;
public:
	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(const Vector3& v, float angle);
	Quaternion(const Quaternion& other);
	Quaternion(const Matrix4x4& mat);
	Quaternion(const Vector4& v);
};

Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);

Quaternion& operator += (Quaternion& q1, const Quaternion q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);

float		Dot(const Quaternion& q1, const Quaternion& q2);
float		Length(const Quaternion& q);
Quaternion	Normalized(const Quaternion& q);
Quaternion	Slerp(const Quaternion& start, const Quaternion& end, float t);

#endif