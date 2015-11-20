#include "Vector4.h"
#include <cmath>

Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
Vector4::Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
Vector4::~Vector4() {}

Vector4 Vector4::Normalized(){
	return Normalized(Vector4(x, y, z, w));
}
void Vector4::Normalize(){
	Vector4 result = Normalized();
	x = result.x;
	y = result.y;
	z = result.z;
	w = result.w;
}
float Vector4::Length(){
	return Length(Vector4(x, y, z, w));
}
float Vector4::Dot(const Vector4& v){
	return Dot(Vector4(x, y, z, w), v);
}

Vector4	Vector4::Normalized	(const Vector4& v){
	return v / Length(v);
}
float	Vector4::Length		(const Vector4& v){
	return sqrt(Dot(v, v));
}
float	Vector4::Angle		(const Vector4& from,	const Vector4& to){
	return 0.0f;
}
float	Vector4::Distance	(const Vector4& v1,		const Vector4& v2){
	return Length(v2 - v1);
}
float	Vector4::Dot			(const Vector4& v1,		const Vector4& v2){
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
Vector4	Vector4::Lerp		(const Vector4& start,	const Vector4& end,		float t){
	return start * (1.0f - t) + end * t;
}
Vector4	Vector4::Clamp		(const Vector4& value,	const Vector4& min,		const Vector4& max){
	return Min(max, Max(min, value));
}
Vector4	Vector4::Max			(const Vector4& v1,		const Vector4& v2){
	return (v1 >= v2) ? v1 : v2;
}
Vector4	Vector4::Min			(const Vector4& v1,		const Vector4& v2){
	return (v1 <= v2) ? v1 : v2;
}

Vector4	operator - (const Vector4& v){
	return Vector4(-v.x, -v.y, -v.z, -v.w);
}
Vector4	operator + (const Vector4& v){
	return v;
}

Vector4& operator += (Vector4& v1, const Vector4& v2){
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}
Vector4& operator -= (Vector4& v1, const Vector4& v2){
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return v1;
}
Vector4& operator *= (Vector4& v, float s){
	v.x *= s;
	v.y *= s;
	v.z *= s;
	v.w *= s;
	return v;
}
Vector4& operator /= (Vector4& v, float s){
	v.x /= s;
	v.y /= s;
	v.z /= s;
	v.w /= s;
	return v;
}

bool operator != (const Vector4& v1, const Vector4& v2){
	return !(v1 == v2);
}
bool operator == (const Vector4& v1, const Vector4& v2){
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
}
bool operator <= (const Vector4& v1, const Vector4& v2){
	return (v1.x <= v2.x) && (v1.y <= v2.y) && (v1.z <= v2.z) && (v1.w <= v2.w);
}
bool operator >= (const Vector4& v1, const Vector4& v2){
	return v2 <= v1;
}

Vector4 operator + (Vector4 v1, const Vector4& v2){
	return v1 += v2;
}
Vector4 operator - (Vector4 v1, const Vector4& v2){
	return v1 -= v2;
}
Vector4 operator * (Vector4 v, float s){
	return v *= s;
}
Vector4 operator * (float s, Vector4 v){
	return v *= s;
}
Vector4 operator / (Vector4 v, float s){
	return v /= s;
}