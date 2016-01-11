#ifndef D_LIGHT_H
#define D_LIGHT_H

#include "../../Interface/ILight.h"
#include "../Vector3.h"
#include "../Color32.h"

class DLight : public ILight{
public:
	Color32 m_Diffuse;
	Color32 m_Specular;
	Color32 m_Ambient;
	Vector3 m_position;
public:
	DLight(Color32& specular, Color32& diffuse, Color32& ambient, Vector3& pos);
	~DLight();
	virtual void SetAmbient(Color32& ambient) override;
	virtual void SetDiffuse(Color32& diffuse) override;
	virtual void SetSpecular(Color32& specular) override;
	virtual void SetPosition(Vector3& pos) override;
	Color32* GetAmbientDPtr();
	Color32* GetSpecularDPtr();
	Color32* GetDiffuseDPtr();
	Vector3* GetPositionDPtr();
};

#endif