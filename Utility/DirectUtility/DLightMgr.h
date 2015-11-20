#ifndef D_LIGHT_MGR_H
#define D_LIGHT_MGR_H

#include "../../Interface/ILightMgr.h"
#include "../../DirectDefine.h"

class DLightMgr : public ILightMgr{
public:
	LPDIRECT3DDEVICE9 m_pDev;
public:
	DLightMgr(LPDIRECT3DDEVICE9 pDev);
	~DLightMgr();
	virtual void AddLight(Color3& specular, Color3& diffuse, Color3& ambient, Vector3& pos) override;
	virtual void AddLight(ILight* pLight) override;
};

#endif