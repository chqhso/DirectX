#include "Vector3.h"
#include "DirectUtility\DVector3.h"
#include <cmath>

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vector3 Vector3::Normalized(){
	return Normalized(Vector3(x, y, z));
}
void Vector3::Normalize(){
	Vector3 result = Normalized();
	x = result.x;
	y = result.y;
	z = result.z;
}
float Vector3::Length(){
	return Length(Vector3(x, y, z));
}
float Vector3::Dot(const Vector3& v){
	return Dot(Vector3(x, y, z), v);
}
Vector3 Vector3::Cross(const Vector3& v){
	return Cross(Vector3(x, y, z), v);
}

Vector3	Vector3::Normalized	(const Vector3& v){
	return v / Length(v);
}
float	Vector3::Length		(const Vector3& v){
	return sqrt(Dot(v, v));
}
float	Vector3::Angle		(const Vector3& from,	const Vector3& to){
//	return atan2(to.y, from.x);
	return 0.0f;
}
float	Vector3::Distance	(const Vector3& v1,		const Vector3& v2){
	return Length(v2 - v1);
}
float	Vector3::Dot			(const Vector3& v1,		const Vector3& v2){
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
Vector3	Vector3::Cross		(const Vector3& v1,		const Vector3& v2){
	Vector3 result(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
	return result;
}
Vector3	Vector3::Lerp		(const Vector3& start,	const Vector3& end,	float t){
	return start * (1.0f - t) + end * t;
}
Vector3 Vector3::Clamp		(const Vector3& value,	const Vector3& min,	const Vector3& max){
	return Min(max, Max(min, value));
}
Vector3 Vector3::Max			(const Vector3& v1,		const Vector3& v2){
	return (v1 >= v2) ? v1 : v2;
}
Vector3 Vector3::Min			(const Vector3& v1,		const Vector3& v2){
	return (v1 <= v2) ? v1 : v2;
}

Vector3 operator - (const Vector3& v){
	return Vector3(-v.x, -v.y, -v.z);
}
Vector3 operator + (const Vector3& v){
	return v;
}

Vector3& operator += (Vector3& v1, const Vector3& v2){
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}
Vector3& operator -= (Vector3& v1, const Vector3& v2){
	return v1 += -v2;
}
Vector3& operator *= (Vector3& v1, float s){
	v1.x *= s;
	v1.y *= s;
	v1.z *= s;
	return v1;
}
Vector3& operator /= (Vector3& v1, float s){
	v1.x /= s;
	v1.y /= s;
	v1.z /= s;
	return v1;
}

bool operator != (const Vector3 v1, const Vector3& v2){
	return !(v1 == v2);
}
bool operator == (const Vector3 v1, const Vector3& v2){
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}
bool operator <= (const Vector3 v1, const Vector3& v2){
	return (v1.x <= v2.x) && (v1.y <= v2.y) && (v1.z <= v2.z);
}
bool operator >= (const Vector3 v1, const Vector3& v2){
	return (v2 <= v1);
}

Vector3 operator + (Vector3 v1, const Vector3& v2){
	return v1 += v2;
}
Vector3 operator - (Vector3 v1, const Vector3& v2){
	return v1 -= v2;
}
Vector3 operator * (Vector3 v, float s){
	return v *= s;
}
Vector3 operator * (float s, Vector3 v){
	return v *= s;
}
Vector3 operator / (Vector3 v, float s){
	return v /= s;
}