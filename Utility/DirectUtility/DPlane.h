#ifndef D_PLANE_H
#define D_PLANE_H

#include "../../DirectDefine.h"
#include "../Plane.h"

class DPlane{
public:
	D3DXPLANE m_Plane;
public:
	DPlane();
	DPlane(float a, float b, float c, float d);
	DPlane(const Plane& plane);
	void Copy(Plane* plane);
};

#endif