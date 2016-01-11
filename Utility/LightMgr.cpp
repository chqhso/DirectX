#include "LightMgr.h"
#include "Light.h"

LightMgr::LightMgr(){}
LightMgr::~LightMgr(){}
bool LightMgr::AddLight(int index, const Color32& specular, const Color32& diffuse, const Color32& ambient, const Vector3& pos){
	Light* light = new Light(diffuse, specular, ambient, pos);
	return AddLight(index, light);
}
bool LightMgr::AddLight(int index, ILight* light){
	if (m_pLightList.find(index) != m_pLightList.end())
		return false;
	m_pLightList.emplace(index, light);
	return true;
}