#include "Vector2.h"
#include <cmath>

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y) {}
Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}

Vector2 operator - (const Vector2& v){
	return Vector2(-v.x, -v.y);
}
Vector2 operator + (const Vector2& v){
	return v;
}

Vector2& operator += (Vector2& v1, const Vector2& v2){
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}
Vector2& operator -= (Vector2& v1, const Vector2& v2){
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}
Vector2& operator *= (Vector2& v, float s){
	v.x *= s;
	v.y *= s;
	return v;
}
Vector2& operator /= (Vector2& v, float s){
	v.x /= s;
	v.y /= s;
	return v;
}

bool operator != (const Vector2& v1, const Vector2& v2){
	return !(v1 == v2);
}
bool operator == (const Vector2& v1, const Vector2& v2){
	return (v1.x == v2.x) && (v1.y == v2.y);
}
bool operator <= (const Vector2& v1, const Vector2& v2){
	return (v1.x <= v2.x) && (v1.y <= v2.y);
}
bool operator >= (const Vector2& v1, const Vector2& v2){
	return (v2 <= v1);
}

Vector2 operator + (Vector2 v1, const Vector2& v2){
	return v1 += v2;
}
Vector2 operator - (Vector2 v1, const Vector2& v2){
	return v1 -= v2;
}
Vector2 operator * (Vector2 v, float s){
	return v *= s;
}
Vector2 operator * (float s, Vector2 v){
	return v *= s;
}
Vector2 operator / (Vector2 v, float s){
	return v /= s;
}

Vector2	Normalized(const Vector2& v){
	return v / Length(v);
}
float	Length(const Vector2& v){
	return sqrt(Dot(v, v));
}
float	Angle(const Vector2& from, const Vector2& to){
	return atan2(to.y, from.x);
}
float	Distance(const Vector2& v1, const Vector2& v2){
	return Length(v2 - v1);
}
float	Dot(const Vector2& v1, const Vector2& v2){
	return v1.x * v2.x + v1.y * v2.y;
}
Vector2	Lerp(const Vector2& start, const Vector2& end, float t){
	return start * (1.0f - t) + end * t;
}
Vector2	Clamp(const Vector2& value, const Vector2& min, const Vector2& max){
	return Min(max, Max(min, value));
}
Vector2	Max(const Vector2& v1, const Vector2& v2){
	return (v1 >= v2) ? v1 : v2;
}
Vector2	Min(const Vector2& v1, const Vector2& v2){
	return (v1 <= v2) ? v1 : v2;
}