#ifndef VECTOR4_H
#define VECTOR4_H

class Vector4{
public:
	float x, y, z, w;
public:
	Vector4();
	Vector4(const Vector4& other);
	Vector4(float _x, float _y, float _z, float _w);
	~Vector4();
public:
	Vector4 Normalized();
	void Normalize();
	float Length();
	float Dot(const Vector4& v);
public:
	static	Vector4	Normalized	(const Vector4& v);
	static	float	Length		(const Vector4& v);
	/// TODO
	static	float	Angle		(const Vector4& from,	const Vector4& to);
	static	float	Distance	(const Vector4& v1,		const Vector4& v2);
	static	float	Dot			(const Vector4& v1,		const Vector4& v2);
	static	Vector4	Lerp		(const Vector4& start,	const Vector4& end,		float t);
	static	Vector4	Clamp		(const Vector4& value,	const Vector4& min,		const Vector4& max);
	static	Vector4	Max			(const Vector4& v1,		const Vector4& v2);
	static	Vector4	Min			(const Vector4& v1,		const Vector4& v2);
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

#endif