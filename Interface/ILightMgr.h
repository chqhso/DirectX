#ifndef I_LIGHT_MGR_H
#define I_LIGHT_MGR_H

#include "../Define.h"
#include "ILight.h"

class ILightMgr{
protected:
	std::vector<ILight*>	m_pLightList;
public:
	ILightMgr(){ 
	}
	virtual ~ILightMgr(){
		for (auto i : m_pLightList){
			DEL(i);
		}
	}
	virtual void AddLight(Color3& specular, Color3& diffuse, Color3& ambient, Vector3& pos) = 0;
	virtual void AddLight(ILight* pLight) = 0;
	ILight* GetLightPtr(int index){
		return m_pLightList[index];
	}
	int GetLightCount(){
		return m_pLightList.size();
	}
};

#endif