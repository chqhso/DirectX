#ifndef VECTOR4_H
#define VECTOR4_H

struct Vector4{
public:
	float x, y, z, w;
public:
	Vector4();
	Vector4(const Vector4& other);
	Vector4(float _x, float _y, float _z, float _w);
};

Vector4	operator - (const Vector4& v);
Vector4	operator + (const Vector4& v);

Vector4& operator += (Vector4& v1, const Vector4& v2);
Vector4& operator -= (Vector4& v1, const Vector4& v2);
Vector4& operator *= (Vector4& v, float s);
Vector4& operator /= (Vector4& v, float s);

bool operator != (const Vector4& v1, const Vector4& v2);
bool operator == (const Vector4& v1, const Vector4& v2);
bool operator <= (const Vector4& v1, const Vector4& v2);
bool operator >= (const Vector4& v1, const Vector4& v2);

Vector4 operator + (Vector4 v1, const Vector4& v2);
Vector4 operator - (Vector4 v1, const Vector4& v2);
Vector4 operator * (Vector4 v, float s);
Vector4 operator * (float s, Vector4 v);
Vector4 operator / (Vector4 v, float s);

Vector4	Normalized(const Vector4& v);
float	Length(const Vector4& v);
/// TODO
float	Angle(const Vector4& from, const Vector4& to);
float	Distance(const Vector4& v1, const Vector4& v2);
float	Dot(const Vector4& v1, const Vector4& v2);
Vector4	Lerp(const Vector4& start, const Vector4& end, float t);
Vector4	Clamp(const Vector4& value, const Vector4& min, const Vector4& max);
Vector4	Max(const Vector4& v1, const Vector4& v2);
Vector4	Min(const Vector4& v1, const Vector4& v2);

#endif