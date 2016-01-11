#ifndef LIGHT_H
#define LIGHT_H

#include "../Interface/ILight.h"
#include "Color32.h"
#include "Vector3.h"

class Light : public ILight{
public:
	Color32 m_diffuse;
	Color32 m_specular;
	Color32 m_ambient;
	Vector3 m_position;
public:
	Light(const Color32& diffuse, const Color32& specular, const Color32& ambient, const Vector3& pos);
	virtual ~Light();
	virtual void SetAmbient(const Color32& color) override;
	virtual void SetDiffuse(const Color32& color) override;
	virtual void SetSpecular(const Color32& color) override;
	virtual void SetPosition(const Vector3& pos) override;
	virtual const Color32& GetAmbient() override;
	virtual const Color32& GetDiffuse() override;
	virtual const Color32& GetSpecular() override;
	virtual const Vector3& GetPosition() override;
};

#endif