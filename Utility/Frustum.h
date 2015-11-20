#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "../Interface/IFrustum.h"
#include "Plane.h"

#define PLANE_EPSILON 5.0f

class Frustum : public IFrustum{
	Vector3 m_vtx[8];
	Vector3 m_vPos;
	Plane m_plane[6];
public:
	Frustum();
	virtual ~Frustum();
	virtual void Make(float* matView, float* matProj) override;
	virtual void Make(Matrix4x4* matView, Matrix4x4* matProj) override;
	virtual bool IsIn(Vector3* pv) override;
	virtual bool IsInSphere(Vector3* pv, float radius) override;
	virtual Vector3* GetPosPtr() { return &m_vPos; }
};

#endif