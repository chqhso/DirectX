#ifndef XML_MGR_H
#define XML_MGR_H

#include "../Interface/IXMLMgr.h"
//#include "../Interface/INodeMgr.h"
//#include "../NodeMgr.h"

class XMLMgr : public IXMLMgr{
public:
	XMLMgr(LPDIRECT3DDEVICE9 pDev);
	virtual ~XMLMgr() override;
	virtual void Regist(XMLID id, std::string filename) override;
	virtual void Load() override;
	virtual void ShutDown() override;
	INodeMgr* GetParsedData(XMLID id);
private:
	LPDIRECT3DDEVICE9 m_pDev;
	KParser* m_pParser;
	std::map<XMLID, std::string> m_Data;
//	std::map<XMLID, KParsedData*> m_ParsedDataBuff;
	std::map<XMLID, INodeMgr*> m_NodeMgrBuff;
};

#endif