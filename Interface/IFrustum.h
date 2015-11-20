#ifndef I_FRUSTUM_H
#define I_FRUSTUM_H

#include "../Define.h"

class IFrustum{
public:
	IFrustum(){}
	virtual ~IFrustum(){}
	virtual void Make(float* matView, float* matProj) = 0;
	virtual void Make(Matrix4x4* matView, Matrix4x4* matProj) = 0;
	virtual bool IsIn(Vector3* pv) = 0;
	virtual bool IsInSphere(Vector3* pv, float radius) = 0;
	virtual Vector3* GetPosPtr() = 0;
};

#endif