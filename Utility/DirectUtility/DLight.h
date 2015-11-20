#ifndef D_LIGHT_H
#define D_LIGHT_H

#include "../../Interface/ILight.h"
#include "DColor4.h"
#include "DVector4.h"

class DLight : public ILight{
public:
	DColor4 m_Diffuse;
	DColor4 m_Specular;
	DColor4 m_Ambient;
	DVector4 m_position;
public:
	DLight(Color3& specular, Color3& diffuse, Color3& ambient, Vector3& pos);
	~DLight();
	virtual void SetAmbient(Color3& ambient) override;
	virtual void SetDiffuse(Color3& diffuse) override;
	virtual void SetSpecular(Color3& specular) override;
	virtual void SetPosition(Vector3& pos) override;
	virtual float* GetAmbientFPtr() override;
	virtual float* GetDiffuseFPtr() override;
	virtual float* GetSpecularFPtr() override;
	virtual float* GetPositionFPtr() override;
	DColor4* GetAmbientDPtr();
	DColor4* GetSpecularDPtr();
	DColor4* GetDiffuseDPtr();
	DVector4* GetPositionDPtr();
};

#endif