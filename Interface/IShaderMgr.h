#ifndef I_SHADER_MGR_H
#define I_SHADER_MGR_H

#include "../Define.h"

#include "../Resources/PSMgr.h"
#include "../Resources/VSMgr.h"

enum class PS_ID;
enum class VS_ID;

class IShaderMgr{
public:
	IShaderMgr(){}
	virtual ~IShaderMgr(){}
	virtual void Regist(PS_ID id, std::string filename) = 0;
	virtual void Regist(VS_ID id, std::string filename) = 0;
	virtual void Load() = 0;
	virtual void ShutDown() = 0;
	// TODO : 인터페이스 생성후 교체 예정
	virtual PSMgr* GetPSMgr(PS_ID id) = 0;
	virtual VSMgr* GetVSMgr(VS_ID id) = 0;
};

#endif