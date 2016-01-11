#ifndef LIGHT_MGR_H
#define LIGHT_MGR_H

#include "../Interface/ILightMgr.h"

class LightMgr : public ILightMgr{
public:
	LightMgr();
	virtual ~LightMgr();
	virtual bool AddLight(int index, const Color32& specular, const Color32& diffuse, const Color32& ambient, const Vector3& pos) override;
	virtual bool AddLight(int index, ILight* light) override;
};

#endif