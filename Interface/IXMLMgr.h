#ifndef I_XML_MGR_H
#define I_XML_MGR_H

#include "../Define.h"
#include "INodeMgr.h"
//class INodeMgr;

enum class XMLID;

class IXMLMgr{
public:
	IXMLMgr(){}
	virtual ~IXMLMgr(){}
	virtual void Regist(XMLID id, std::string filename) = 0;
	virtual void Load() = 0;
	virtual void ShutDown() = 0;
	virtual INodeMgr* GetParsedData(XMLID id) = 0;
};

#endif