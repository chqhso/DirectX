#ifndef I_LIGHT_H
#define I_LIGHT_H

#include "../Define.h"

class ILight{
public:
	ILight(){
	}
	virtual ~ILight(){}
	virtual void SetAmbient(Color3& color) = 0;
	virtual void SetDiffuse(Color3& color) = 0;
	virtual void SetSpecular(Color3& color) = 0;
	virtual void SetPosition(Vector3& pos) = 0;
	virtual float* GetAmbientFPtr() = 0;
	virtual float* GetDiffuseFPtr() = 0;
	virtual float* GetSpecularFPtr() = 0;
	virtual float* GetPositionFPtr() = 0;
};

#endif