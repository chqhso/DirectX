#include "DLightMgr.h"
#include "DLight.h"

DLightMgr::DLightMgr(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){}
DLightMgr::~DLightMgr(){}
void DLightMgr::AddLight(Color3& specular, Color3& diffuse, Color3& ambient, Vector3& pos){
	ILight* pLight = new DLight(specular, diffuse, ambient, pos);
	m_pLightList.push_back(pLight);
}
void DLightMgr::AddLight(ILight* pLight){
	m_pLightList.push_back(pLight);
}