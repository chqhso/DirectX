#include "Plane.h"
#include "Vector4.h";

Plane::Plane(){
	a = 0.0f;
	b = 0.0f;
	c = 0.0f;
	d = 0.0f;
}
Plane::Plane(float _a, float _b, float _c, float _d){
	a = _a;
	b = _b;
	c = _c;
	d = _d;
}
Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2){
	Vector3 vec0, vec1, vec2;
	vec1 = v1 - v0;
	vec2 = v2 - v0;
	vec0 = Cross(vec1, vec2);
//	vec0.Normalize();
	vec0 = Normalized(vec0);
	a = vec0.x;
	b = vec0.y;
	c = vec0.z;
	d = -(vec0.x * v0.x + vec0.y * v0.y + vec0.z * v0.z);
}
float Plane::Dot(const Vector4& v){
	return (a * v.x) + (b * v.y) + (c * v.z) + (d * v.w);
}
float Plane::DotCoord(const Vector3& v){
	return (a * v.x) + (b * v.y) + (c * v.z) + d;
}
float Plane::DotNormal(const Vector3& v){
	return (a * v.x) + (b * v.y) + (c * v.z);
}