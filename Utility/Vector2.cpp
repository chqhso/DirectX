#include "Vector2.h"
#include <cmath>

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y) {}
Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}
Vector2::~Vector2() {}

Vector2 Vector2::Normalized(){
	return Normalized(Vector2(x, y));
}
void Vector2::Normalize(){
	Vector2 result = Normalized();
	x = result.x;
	y = result.y;
}
float Vector2::Length(){
	return Length(Vector2(x, y));
}
float Vector2::Dot(const Vector2& v){
	return Dot(Vector2(x, y), v);
}

Vector2	Vector2::Normalized	(const Vector2& v){
	return v / Length(v);
}
float	Vector2::Length		(const Vector2& v){
	return sqrt(Dot(v, v));
}
float	Vector2::Angle		(const Vector2& from,	const Vector2& to){
	return atan2(to.y, from.x);
}
float	Vector2::Distance	(const Vector2& v1,		const Vector2& v2){
	return Length(v2 - v1);
}
float	Vector2::Dot		(const Vector2& v1,		const Vector2& v2){
	return v1.x * v2.x + v1.y * v2.y;
}
Vector2	Vector2::Lerp		(const Vector2& start,	const Vector2& end,		float t){
	return start * (1.0f - t) + end * t;
}
Vector2	Vector2::Clamp		(const Vector2& value,	const Vector2& min,		const Vector2& max){
	return Min(max, Max(min, value));
}
Vector2	Vector2::Max		(const Vector2& v1,		const Vector2& v2){
	return (v1 >= v2) ? v1 : v2;
}
Vector2	Vector2::Min		(const Vector2& v1,		const Vector2& v2){
	return (v1 <= v2) ? v1 : v2;
}

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