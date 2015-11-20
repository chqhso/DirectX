#ifndef QUATERNION_H
#define QUATERNION_H

class Vector3;
class Vector4;
class Matrix4x4;

class Quaternion{
public:
	float x, y, z, w;
public:
	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(const Vector3& v, float angle);
	Quaternion(const Quaternion& other);
	Quaternion(const Matrix4x4& mat);
	Quaternion(const Vector4& v);
	~Quaternion();
public:
	float Dot(const Quaternion& q);
	float Length();
	Quaternion Normalized();
	void Normalize();
	Matrix4x4 Rotate();
public:
	static float		Dot			(const Quaternion& q1,		const Quaternion& q2);
	static float		Length		(const Quaternion& q);
	static Quaternion	Normalized	(const Quaternion& q);
	static Quaternion	Slerp		(const Quaternion& start,	const Quaternion& end,	float t);
	/// Matrix4x4∑Œ ¿Ãµø
	//static Matrix4x4	Rotate		(const Quaternion& q);
	//static Matrix4x4	Rotate		(const Vector3& v,			float angle);
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

#endif