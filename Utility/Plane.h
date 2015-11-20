#ifndef PLANE_H
#define PLANE_H

#include "../Define.h"

class Plane{
public:
	float a, b, c, d;
public:
	Plane();
	Plane(float _a, float _b, float _c, float _d);
	Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	float Dot(const Vector4& v);
	float DotCoord(const Vector3& v);
	float DotNormal(const Vector3& v);
};

#endif