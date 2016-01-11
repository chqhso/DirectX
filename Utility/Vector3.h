#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3{
public:
	float x, y, z;
public:
	Vector3();
	Vector3(const Vector3& other);
	Vector3(float _x, float _y, float _z);
};

Vector3 operator - (const Vector3& v);
Vector3 operator + (const Vector3& v);

Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v1, float s);
Vector3& operator /= (Vector3& v1, float s);

bool operator != (const Vector3 v1, const Vector3& v2);
bool operator == (const Vector3 v1, const Vector3& v2);
bool operator <= (const Vector3 v1, const Vector3& v2);
bool operator >= (const Vector3 v1, const Vector3& v2);

Vector3 operator + (Vector3 v1, const Vector3& v2);
Vector3 operator - (Vector3 v1, const Vector3& v2);
Vector3 operator * (Vector3 v, float s);
Vector3 operator * (float s, Vector3 v);
Vector3 operator / (Vector3 v, float s);

Vector3	Normalized(const Vector3& v);
float	Length(const Vector3& v);
/// TODO
float	Angle(const Vector3& from, const Vector3& to);
float	Distance(const Vector3& v1, const Vector3& v2);
float	Dot(const Vector3& v1, const Vector3& v2);
Vector3	Cross(const Vector3& v1, const Vector3& v2);
Vector3	Lerp(const Vector3& start, const Vector3& end, float t);
Vector3 Clamp(const Vector3& value, const Vector3& min, const Vector3& max);
Vector3 Max(const Vector3& v1, const Vector3& v2);
Vector3 Min(const Vector3& v1, const Vector3& v2);

#endif