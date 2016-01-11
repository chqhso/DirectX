#ifndef I_LIGHT_MGR_H
#define I_LIGHT_MGR_H

#include "../Define.h"
#include <map>
#include "ILight.h"

class ILightMgr{
protected:
	//std::vector<ILight*>	m_pLightList;
	std::map<int, ILight*> m_pLightList;
public:
	ILightMgr(){ 
	}
	virtual ~ILightMgr(){
		for (auto i : m_pLightList){
			DEL(i.second);
		}
	}
	virtual bool AddLight(int index, const Color32& specular, const Color32& diffuse, const Color32& ambient, const Vector3& pos) = 0;
	virtual bool AddLight(int index, ILight* pLight) = 0;
	ILight& GetLight(int index){
		return *m_pLightList[index];
	}
	int GetLightCount(){
		return m_pLightList.size();
	}
};

#endif