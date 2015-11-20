#include "XMLMgr.h"
#include "../Parser/KParser.h"
#include "../NodeMgr.h"

XMLMgr::XMLMgr(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){
	m_pParser = new KParser();
	m_Data.clear();
	//m_ParsedDataBuff.clear();
	m_NodeMgrBuff.clear();
}
XMLMgr::~XMLMgr(){
	ShutDown();
}
void XMLMgr::Regist(XMLID id, std::string filename){
	m_Data.emplace(id, filename);
}
void XMLMgr::Load(){
	for (auto i : m_Data){
		if (m_NodeMgrBuff.find(i.first) != m_NodeMgrBuff.end()){
			continue;
		}
		KParsedData* pParsedData = new KParsedData();
		if (!m_pParser->Parse(pParsedData, i.second.c_str())){
			KLog::Instance()->Log("File load Faile");
			DEL(pParsedData);
			continue;
		}
		INodeMgr* pData = new NodeMgr(m_pDev, pParsedData);

		m_NodeMgrBuff.emplace(i.first, pData);

		DEL(pParsedData);
	}
}
void XMLMgr::ShutDown(){
	for (auto i : m_NodeMgrBuff){
		DEL(i.second);
	}
	m_NodeMgrBuff.clear();
	m_Data.clear();
}
INodeMgr* XMLMgr::GetParsedData(XMLID id){
	return m_NodeMgrBuff[id];
}