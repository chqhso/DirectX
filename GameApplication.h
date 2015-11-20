#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "Application.h"
//#include "Resources\ResourcesMgr.h"
#include "Interface\IResourcesMgr.h"
#include "Interface\ICamera.h"
#include "Interface\ILightMgr.h"
#include "Interface\IFrustum.h"
#include "Interface\ITerrain.h"
#include "Interface\IInput.h"

#include "Resources\PSMgr.h"
#include "Resources\VSMgr.h"

class GameApplication : public Application{
public:
	GameApplication(HINSTANCE);
	~GameApplication();
	virtual void initialize();
	virtual void update(float frameTimer);
	virtual void draw();
	virtual void finish();
private:
//	ResourcesMgr		m_resourcesMgr;
	IResourcesMgr*		m_IResourcesMgr;
	ICamera*			m_ICameraPtr;
	ILightMgr*			m_ILightMgrPtr;
	IFrustum*			m_IFrustumPtr;
	ITerrain*			m_ITerrainPtr;
	IInput*				m_IInput;

	VSMgr*				m_pVSMgr;
	PSMgr*				m_pPSMgr;
	VSMgr*				m_pTeVSMgr;
	PSMgr*				m_pTePSMgr;

	float testframe;

	bool asdf;
};

#endif