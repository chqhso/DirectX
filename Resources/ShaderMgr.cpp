#include "ShaderMgr.h"

ShaderMgr::ShaderMgr(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){
	ShutDown();
}
ShaderMgr::~ShaderMgr(){
	ShutDown();
}
//void ShaderMgr::Regist(ShaderID id, std::string filename){
//	m_Data.emplace(id, filename);
//}
void ShaderMgr::Regist(PS_ID id, std::string filename){
	m_PSData.emplace(id, filename);
}
void ShaderMgr::Regist(VS_ID id, std::string filename){
	m_VSData.emplace(id, filename);
}
//void ShaderMgr::Regist(FX_ID id, std::string filename){
//	m_FXData.emplace(id, filename);
//}
void ShaderMgr::Load(){
	for (auto i : m_PSData){
		if (m_PSBuff.find(i.first) != m_PSBuff.end()){
			continue;
		}
		PSMgr* ps = new PSMgr(m_pDev);
		ps->Load(i.second);
		m_PSBuff.emplace(i.first, ps);
	}
	for (auto i : m_VSData){
		if (m_VSBuff.find(i.first) != m_VSBuff.end()){
			continue;
		}
		VSMgr* vs = new VSMgr(m_pDev);
		vs->Load(i.second);
		m_VSBuff.emplace(i.first, vs);
	}
	//for (auto i : m_FXData){
	//	if (m_FXBuff.find(i.first) != m_FXBuff.end()){
	//		continue;
	//	}
	//	FXMgr* fx = new FXMgr(m_pDev);
	//	fx->Load(i.second);
	//	m_FXBuff.emplace(i.first, fx);
	//}
}
void ShaderMgr::ShutDown(){
	for (auto i : m_VSBuff){
		DEL(i.second);
	}
	for (auto i : m_PSBuff){
		DEL(i.second);
	}
	//for (auto i : m_FXBuff){
	//	DEL(i.second);
	//}
	m_VSBuff.clear();
	m_PSBuff.clear();
	m_PSData.clear();
	m_VSData.clear();
	//m_FXData.clear();
}
VSMgr* ShaderMgr::GetVSMgr(VS_ID id){
	return m_VSBuff[id];
}
PSMgr* ShaderMgr::GetPSMgr(PS_ID id){
	return m_PSBuff[id];
}
//FXMgr* ShaderMgr::GetFXMgr(FX_ID id){
//	return m_FXBuff[id];
//}