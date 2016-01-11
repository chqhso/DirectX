#ifndef I_LIGHT_H
#define I_LIGHT_H

struct Color32;
struct Vector3;

class ILight{
public:
	ILight(){}
	virtual ~ILight(){}
	virtual void SetAmbient(const Color32& color) = 0;
	virtual void SetDiffuse(const Color32& color) = 0;
	virtual void SetSpecular(const Color32& color) = 0;
	virtual void SetPosition(const Vector3& pos) = 0;
	virtual const Color32& GetAmbient() = 0;
	virtual const Color32& GetDiffuse() = 0;
	virtual const Color32& GetSpecular() = 0;
	virtual const Vector3& GetPosition() = 0;
};

#endif