#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2{
public:
	float		x, y;
public:
	Vector2();
	Vector2(const Vector2& other);
	Vector2(float _x, float _y);
};
Vector2 operator - (const Vector2& v);
Vector2 operator + (const Vector2& v);

Vector2& operator += (Vector2& v1, const Vector2& v2);
Vector2& operator -= (Vector2& v1, const Vector2& v2);
Vector2& operator *= (Vector2& v, float s);
Vector2& operator /= (Vector2& v, float s);

bool operator != (const Vector2& v1, const Vector2& v2);
bool operator == (const Vector2& v1, const Vector2& v2);
bool operator <= (const Vector2& v1, const Vector2& v2);
bool operator >= (const Vector2& v1, const Vector2& v2);

Vector2 operator + (Vector2 v1, const Vector2& v2);
Vector2 operator - (Vector2 v1, const Vector2& v2);
Vector2 operator * (Vector2 v, float s);
Vector2 operator * (float s, Vector2 v);
Vector2 operator / (Vector2 v, float s);


Vector2	Normalized(const Vector2& v);
float	Length(const Vector2& v);
float	Angle(const Vector2& from, const Vector2& to);
float	Distance(const Vector2& v1, const Vector2& v2);
float	Dot(const Vector2& v1, const Vector2& v2);
Vector2	Lerp(const Vector2& start, const Vector2& end, float t);
Vector2	Clamp(const Vector2& value, const Vector2& min, const Vector2& max);
Vector2	Max(const Vector2& v1, const Vector2& v2);
Vector2	Min(const Vector2& v1, const Vector2& v2);

#endif